#include "step.hpp"

#include <print>

#include <spdlog/spdlog.h>

#include "cli.hpp"
#include "ctx.hpp"

namespace bxx {
step::step(private_tag, ptr<ctx> ctx, fs::path exe, argv args, env_map env)
    : m_ctx(ctx)
    , m_exe(exe)
    , m_args(args)
    , m_env(env) {}

ptr<step> step::create(ptr<ctx> ctx, fs::path exe, argv args, env_map env) {
  return std::make_shared<step>(private_tag{}, ctx, exe, args, env);
}

ptr<step> step::get() { return shared_from_this(); }

const step::argv& step::opts() const { return m_args; }

ptr<step> step::add_opt(std::string opt) {
  m_args.emplace_back(std::move(opt));
  return get();
}

ptr<step> step::add_opt(argv opts) {
  for (auto& opt : opts) {
    add_opt(std::move(opt));
  }

  return get();
}

const std::string& step::msg() const { return m_message; }

ptr<step> step::add_msg(std::string msg) {
  m_message = msg;
  return get();
}

const step::env_map& step::env() const { return m_env; }

ptr<step> step::add_env(env::key k, env::value v) {
  m_env[k] = v;
  return get();
}

ptr<step> step::depends_on(ptr<step> other) {
  m_pre.push_back(other);
  return get();
}

ptr<step> step::install() {
  m_ctx->install_step(get());
  return get();
}

bool step::is_done() const { return m_rc != RC_NOT_EXEC; }

int step::exec() {
  for (auto pre : m_pre) {
    if (!pre->is_done()) {
      pre->exec();
    }
  }

  env_map env;
  for (const auto& kv : env::current()) {
    env[kv.key()] = kv.value();
  }

  for (const auto& [k, v] : m_env) {
    env[k] = v;
  }

  if (m_message.size()) {
    spdlog::info("{}", m_message);
  }

  if (m_ctx->cli()->is_verbose()) {
    std::stringstream ss;
    ss << m_exe.string();
    for (auto& arg : m_args) {
      ss << arg;
    }
    ss << "\n";

    spdlog::info("{}", ss.view());
  }

  proc::process p(*m_ctx->exec(), m_exe, m_args,
                  proc::process_environment(env));

  m_rc = p.wait();

  if (m_rc != RC_OK) {
    throw std::runtime_error(std::format("step returned exit code {}", m_rc));
  }

  return m_rc;
}
} // namespace bxx
