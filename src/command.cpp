#include "command.hpp"

#include "build_ctx.hpp"

namespace buildxx {
command::command(build_ctx& ctx, std::string name)
    : target(ctx, name) {}

const fs::path& command::get_executable() const { return m_exe; }

command& command::executable(std::string name) {
  m_exe = env::find_executable(name);

  if (!fs::exists(m_exe)) {
    throw std::runtime_error(
        std::format("cannot find executable {} in PATH", name));
  }

  return *this;
}

command& command::option(std::string option) {
  m_argv.emplace_back(std::move(option));
  return *this;
}

command& command::options(step::arguments options) {
  for (auto& option_v : options) {
    option(std::move(option_v));
  }
  return *this;
}

const step::environment_map& command::get_environment() const { return m_env; }

command& command::environment(env::key key, env::value value) {
  m_env[key] = value;
  return *this;
}

command& command::environment(step::environment_map env) {
  for (auto& [k, v] : env) {
    environment(k, v);
  }

  return *this;
}

const std::string& command::get_message() const { return m_msg; }

command& command::message(std::string message) {
  m_msg = std::move(message);
  return *this;
}

void command::create_steps(build_ctx& ctx, toolchain& tc) {
  auto& step = ctx.add_step(m_exe, m_argv, m_env)
                   .message(std::format("Running command {}", name()));
  final_step().depends_on(step);
}
} // namespace buildxx
