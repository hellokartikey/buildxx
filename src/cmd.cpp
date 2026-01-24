#include "cmd.hpp"

#include "ctx.hpp"

namespace bxx {
cmd::cmd(private_tag,
         ptr<ctx> ctx,
         std::string exe,
         step::argv args,
         step::env_map env)
    : target(private_tag{}, exe)
    , m_ctx(ctx)
    , m_step(ctx->add_step(env::find_executable(exe), args, env)
                 ->add_msg(std::format("Running {}", exe))) {}

ptr<cmd>
cmd::create(ptr<ctx> ctx, std::string exe, step::argv args, step::env_map env) {
  return std::make_shared<cmd>(private_tag{}, ctx, exe, args, env);
}

ptr<target> cmd::install() {
  target::install();
  m_step->install();
  return get();
}

ptr<target> cmd::build() {
  target::build();
  bxx::exec(m_step);
  return get();
}

ptr<cmd> cmd::add_opt(std::string opt) {
  m_step->add_opt(std::move(opt));
  return get();
}

ptr<cmd> cmd::add_opt(step::argv opts) {
  m_step->add_opt(std::move(opts));
  return get();
}

const step::env_map& cmd::env() const { return m_step->env(); }

ptr<cmd> cmd::add_env(env::key key, env::value value) {
  m_step->add_env(key, value);
  return get();
}

const std::string& cmd::msg() const { return m_step->msg(); }

ptr<cmd> cmd::add_msg(std::string msg) {
  m_step->add_msg(msg);
  return get();
}
} // namespace bxx
