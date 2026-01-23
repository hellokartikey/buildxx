#ifndef HK_BUILDXX_STEP_HPP
#define HK_BUILDXX_STEP_HPP

#include <string>
#include <vector>

#include "common.hpp"

namespace bxx {
class ctx;

class step {
public:
  using environment = std::unordered_map<env::key, env::value>;
  using arguments = std::vector<std::string>;

  // posix exit code is 8bit unsigned
  static constexpr int RC_NOT_EXEC = 256;

  step(
    ctx& ctx,
    fs::path exe,
    arguments args = {},
    environment env = {}
  );

  ~step() = default;

  // non copyable
  step(const step&) = delete;
  step operator=(const step&) = delete;

  // movable
  step(step&&) = default;
  step& operator=(step&&) = default;

  const arguments& options() const;

  step& add_path_option(fs::path path);

  step& add_option(std::string opt);
  step& add_options(arguments opts);

  const environment& env() const;
  step& add_env(env::key key, env::value value);

  step& depends_on(step& other);
  step& install();

  bool is_done() const;

private:
  int exec();

  friend ctx;

private:
  ctx* m_ctx;

  fs::path m_exe;
  arguments m_args;
  environment m_env;

  int m_rc = RC_NOT_EXEC;

  std::vector<step*> m_pre;
};
}

#endif
