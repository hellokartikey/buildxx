#ifndef HK_BUILDXX_STEP_HPP
#define HK_BUILDXX_STEP_HPP

#include <memory>
#include <string>
#include <vector>

#include "common.hpp"

namespace bxx {
class ctx;

class step;

int exec(std::shared_ptr<step> s);

class step : public std::enable_shared_from_this<step> {
private:
  struct private_tag {};

public:
  using env_map = std::unordered_map<env::key, env::value>;
  using argv = std::vector<std::string>;

  // posix exit code is 8bit unsigned
  static constexpr int RC_NOT_EXEC = 256;
  static constexpr int RC_OK = 0;

  step(private_tag,
       std::shared_ptr<ctx> ctx,
       fs::path exe,
       argv args = {},
       env_map env = {});

  ~step() = default;

  static std::shared_ptr<step> create(std::shared_ptr<ctx> ctx,
                                      fs::path exe,
                                      argv args = {},
                                      env_map env = {});

  std::shared_ptr<step> get();

  const argv& opts() const;

  std::shared_ptr<step> add_opt(std::string opt);
  std::shared_ptr<step> add_opt(argv opts);

  const env_map& env() const;

  std::shared_ptr<step> add_env(env::key key, env::value value);

  std::shared_ptr<step> depends_on(std::shared_ptr<step> other);

  std::shared_ptr<step> install();

  bool is_done() const;

private:
  friend int exec(std::shared_ptr<step> s) { return s->exec(); }
  int exec();

private:
  std::shared_ptr<ctx> m_ctx;

  fs::path m_exe;
  argv m_args;
  env_map m_env;

  int m_rc = RC_NOT_EXEC;

  std::vector<std::shared_ptr<step>> m_pre;
};
} // namespace bxx

#endif
