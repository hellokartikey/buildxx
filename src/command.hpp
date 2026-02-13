#ifndef HK_BUILDXX_COMMAND_HPP
#define HK_BUILDXX_COMMAND_HPP

#include "step.hpp"
#include "target.hpp"

namespace buildxx {
class command : public target {
public:
  command(build_ctx& ctx, std::string name);
  ~command() = default;

  const fs::path& get_executable() const;
  command& executable(std::string name);

  const step::arguments& get_options() const;
  command& option(std::string option);
  command& options(step::arguments options);

  const step::environment_map& get_environment() const;
  command& environment(env::key key, env::value value);
  command& environment(step::environment_map environment);

  const std::string& get_message() const;
  command& message(std::string msg);

private:
  void create_steps(build_ctx& ctx, toolchain& tc) override;

private:
  fs::path m_exe{};
  step::arguments m_argv{};
  step::environment_map m_env{};

  std::string m_msg{};

  step* m_step{};
};
} // namespace buildxx

#endif
