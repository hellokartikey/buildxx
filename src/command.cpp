#include "command.hpp"

#include "build_ctx.hpp"

namespace buildxx {
command::command(build_ctx& ctx,
                 std::string exe,
                 step::arguments args,
                 step::environment_map env)
    : target(ctx)
    , m_exe(env::find_executable(exe))
    , m_argv(args)
    , m_env(env) {
  if (!fs::exists(m_exe)) {
    throw std::runtime_error(
        std::format("cannot find executable {} in PATH", exe));
  }
}

command& command::add_option(std::string option) {
  m_argv.emplace_back(std::move(option));
  return *this;
}

command& command::add_option(step::arguments options) {
  for (auto& option : options) {
    add_option(std::move(option));
  }
  return *this;
}

const step::environment_map& command::environment() const { return m_env; }

command& command::add_environment(env::key key, env::value value) {
  m_env[key] = value;
  return *this;
}

const std::string& command::message() const { return m_msg; }

command& command::add_message(std::string message) {
  m_msg = std::move(message);
  return *this;
}

void command::create_steps(build_ctx& ctx, toolchain& tc) {
  auto& step = ctx.add_step(m_exe, m_argv, m_env);
  final_step().depends_on(step);
}
} // namespace buildxx
