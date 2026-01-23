#include "step.hpp"

#include "ctx.hpp"

#include <print>

namespace bxx {
step::step(ctx& ctx, fs::path exe, arguments args, environment env)
  : m_ctx(&ctx)
  , m_exe(exe)
  , m_args(args)
  , m_env(env)
  {
    for (const auto& kv : env::current()) {
      m_env[kv.key()] = kv.value();
    }
  }

const step::arguments& step::options() const { return m_args; }

step& step::add_path_option(fs::path path) {
  return add_option(path.string());
}

step& step::add_option(std::string opt) {
  m_args.emplace_back(std::move(opt));
  return *this;
}

step& step::add_options(arguments opts) {
  for (auto& opt : opts) {
    add_option(std::move(opt));
  }

  return *this;
}

const step::environment& step::env() const { return m_env; }

step& step::add_env(env::key k, env::value v) { m_env[k] = v; return *this; }

step& step::depends_on(step& other) {
  m_pre.push_back(&other);
  return *this;
}

step& step::install() {
  m_ctx->install_step(*this);
  return *this;
}

bool step::is_done() const { return m_rc != RC_NOT_EXEC; }

int step::exec() {
  for (auto* pre : m_pre) {
    if (! pre->is_done()) {
      pre->exec();
    }
  }

  proc::process p(m_ctx->executor(), m_exe, m_args, m_env);
  return m_rc = p.wait();
}
}
