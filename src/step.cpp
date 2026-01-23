#include "step.hpp"

#include "ctx.hpp"

namespace bxx {
step::step(private_tag,
           std::shared_ptr<ctx> ctx,
           fs::path exe,
           arguments args,
           environment env)
    : m_ctx(ctx)
    , m_exe(exe)
    , m_args(args)
    , m_env(env) {}

std::shared_ptr<step> step::create(std::shared_ptr<ctx> ctx,
                                   fs::path exe,
                                   arguments args,
                                   environment env) {
  return std::make_shared<step>(private_tag{}, ctx, exe, args, env);
}

std::shared_ptr<step> step::get() { return shared_from_this(); }

const step::arguments& step::options() const { return m_args; }

std::shared_ptr<step> step::add_option(std::string opt) {
  m_args.emplace_back(std::move(opt));
  return get();
}

std::shared_ptr<step> step::add_options(arguments opts) {
  for (auto& opt : opts) {
    add_option(std::move(opt));
  }

  return get();
}

const step::environment& step::env() const { return m_env; }

std::shared_ptr<step> step::add_env(env::key k, env::value v) {
  m_env[k] = v;
  return get();
}

std::shared_ptr<step> step::depends_on(std::shared_ptr<step> other) {
  m_pre.push_back(other);
  return get();
}

std::shared_ptr<step> step::install() {
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

  environment env;
  for (const auto& kv : env::current()) {
    env[kv.key()] = kv.value();
  }

  for (const auto& [k, v] : m_env) {
    env[k] = v;
  }

  proc::process p(*m_ctx->executor(), m_exe, m_args,
                  proc::process_environment(env));

  return m_rc = p.wait();
}
} // namespace bxx
