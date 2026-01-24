#ifndef HK_BUILDXX_STEP_HPP
#define HK_BUILDXX_STEP_HPP

#include <memory>
#include <string>
#include <vector>

#include "common.hpp"

namespace bxx {
class ctx;

class step;

int exec(ptr<step> s);

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
       ptr<ctx> ctx,
       fs::path exe,
       argv args = {},
       env_map env = {});

  ~step() = default;

  static ptr<step>
  create(ptr<ctx> ctx, fs::path exe, argv args = {}, env_map env = {});
  ptr<step> get();

  const argv& opts() const;
  ptr<step> add_opt(std::string opt);
  ptr<step> add_opt(argv opts);

  const std::string& msg() const;
  ptr<step> add_msg(std::string msg);

  const env_map& env() const;
  ptr<step> add_env(env::key key, env::value value);

  ptr<step> depends_on(ptr<step> other);
  ptr<step> install();

  bool is_done() const;

private:
  friend int exec(ptr<step> s) { return s->exec(); }
  int exec();

private:
  ptr<ctx> m_ctx;

  fs::path m_exe;
  argv m_args;
  env_map m_env;

  int m_rc = RC_NOT_EXEC;

  std::string m_message;

  std::vector<ptr<step>> m_pre;
};
} // namespace bxx

#endif
