#ifndef HK_BUILDXX_STEP_HPP
#define HK_BUILDXX_STEP_HPP

#include <string>
#include <vector>

#include "common.hpp"

namespace buildxx {
class build_ctx;

class step {
public:
  using environment_map = std::unordered_map<env::key, env::value>;
  using arguments = std::vector<std::string>;

  // posix exit codes are 8bit unsigned
  static constexpr int RC_NOT_EXEC = 256;
  static constexpr int RC_OK = 0;

  step(fs::path exe, arguments args = {}, environment_map = {});
  ~step() = default;

  step& phony(bool is_phony = true);

  step& depends_on(step& other);
  step& depends_on_first(step& other);

  bool is_done() const;
  int run(build_ctx& ctx, bool verbose = false);

  const arguments& options() const;
  step& add_option(std::string option);
  step& add_option(arguments options);

  const std::string& message() const;
  step& add_message(std::string message);

  const environment_map& environment() const;
  step& add_environment(env::key key, env::value value);
  step& add_environment(environment_map env);

private:
  fs::path m_exe;
  arguments m_args;
  environment_map m_env;

  std::vector<step*> m_pre;

  int m_rc = RC_NOT_EXEC;

  std::string m_message;

  bool m_phony{};
};
} // namespace buildxx

#endif
