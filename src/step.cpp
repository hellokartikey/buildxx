#include "step.hpp"

#include <print>

#include <spdlog/spdlog.h>

#include "build_ctx.hpp"

namespace buildxx {
step::step(fs::path exe, arguments args, environment_map env)
    : m_exe(exe)
    , m_args(args)
    , m_env(env) {}

step& step::phony(bool is_phony) {
  m_phony = is_phony;
  return *this;
}

const step::arguments& step::options() const { return m_args; }

step& step::add_option(std::string option) {
  m_args.emplace_back(std::move(option));
  return *this;
}

step& step::add_option(arguments options) {
  for (auto& option : options) {
    add_option(std::move(option));
  }

  return *this;
}

const std::string& step::message() const { return m_message; }

step& step::add_message(std::string message) {
  m_message = std::move(message);
  return *this;
}

const step::environment_map& step::environment() const { return m_env; }

step& step::add_environment(env::key k, env::value v) {
  m_env[k] = v;
  return *this;
}

step& step::add_environment(environment_map environment) {
  for (auto& [k, v] : environment) {
    m_env[k] = v;
  }

  return *this;
}

step& step::depends_on(step& other) {
  m_pre.push_back(&other);
  return *this;
}

step& step::depends_on_first(step& other) {
  m_pre.insert(m_pre.begin(), &other);
  return *this;
}

bool step::is_done() const { return m_rc != RC_NOT_EXEC; }

int step::run(build_ctx& ctx, bool verbose) {
  for (auto* pre : m_pre) {
    if (!pre->is_done()) {
      pre->run(ctx, verbose);
    }
  }

  if (m_phony) {
    return 0;
  }

  environment_map env;
  for (const auto& kv : env::current()) {
    env[kv.key()] = kv.value();
  }

  for (const auto& [k, v] : m_env) {
    env[k] = v;
  }

  if (m_message.size()) {
    spdlog::info("{}", m_message);
  }

  if (verbose) {
    std::stringstream ss;

    ss.write(m_exe.c_str(), m_exe.size());
    ss.put(' ');

    for (auto& arg : m_args) {
      ss.write(arg.c_str(), arg.size());
      ss.put(' ');
    }

    std::println("{}", ss.view());
  }

  proc::process p(ctx.io_context(), m_exe, m_args,
                  proc::process_environment(env));

  m_rc = p.wait();

  if (m_rc != RC_OK) {
    throw std::runtime_error(std::format("step returned exit code {}", m_rc));
  }

  return m_rc;
}
} // namespace buildxx
