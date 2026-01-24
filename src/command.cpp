#include "command.hpp"

#include "ctx.hpp"

namespace bxx {
command::command(private_tag,
                 std::shared_ptr<ctx> ctx,
                 std::string exe,
                 step::arguments args,
                 step::environment env)
    : target(private_tag{}, exe)
    , m_ctx(ctx)
    , m_step(ctx->add_step(env::find_executable(exe), args, env)) {}

std::shared_ptr<command> command::create(std::shared_ptr<ctx> ctx,
                                         std::string exe,
                                         step::arguments args,
                                         step::environment env) {
  return std::make_shared<command>(private_tag{}, ctx, exe, args, env);
}

std::shared_ptr<target> command::install() {
  target::install();
  m_ctx->install_step(m_step);
  return get();
}

std::shared_ptr<target> command::build() {
  target::build();
  exec_step(m_step);
  return get();
}

std::shared_ptr<command> command::add_option(std::string opt) {
  m_step->add_option(std::move(opt));
  return get();
}

std::shared_ptr<command> command::add_options(step::arguments opts) {
  m_step->add_options(std::move(opts));
  return get();
}

const step::environment& command::env() const { return m_step->env(); }

std::shared_ptr<command> command::add_env(env::key key, env::value value) {
  m_step->add_env(key, value);
  return get();
}
} // namespace bxx
