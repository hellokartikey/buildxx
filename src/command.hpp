#ifndef HK_BUILDXX_COMMAND_HPP
#define HK_BUILDXX_COMMAND_HPP

#include "step.hpp"
#include "target.hpp"

namespace buildxx {
class command : public target {
private:
  command(build_ctx& ctx,
          std::string name,
          std::string exe,
          step::arguments args = {},
          step::environment_map env = {});

public:
  ~command() = default;

  static command& add(build_ctx& ctx,
                      std::string name,
                      std::string exe,
                      step::arguments args = {},
                      step::environment_map env = {});

  const step::arguments& options() const;
  command& add_option(std::string option);
  command& add_option(step::arguments options);

  const step::environment_map& environment() const;
  command& add_environment(env::key key, env::value value);
  command& add_environment(step::environment_map environment);

  const std::string& message() const;
  command& add_message(std::string msg);

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
