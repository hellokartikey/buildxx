#ifndef HK_BUILDXX_STEP_HPP
#define HK_BUILDXX_STEP_HPP

#include <string>
#include <memory>
#include <vector>

#include "common.hpp"

namespace bxx {
class ctx;

class step : public std::enable_shared_from_this<step> {
private:
  struct private_tag {};

public:
  using environment = std::unordered_map<env::key, env::value>;
  using arguments = std::vector<std::string>;

  // posix exit code is 8bit unsigned
  static constexpr int RC_NOT_EXEC = 256;

  step(
    private_tag,
    std::shared_ptr<ctx> ctx,
    fs::path exe,
    arguments args = {},
    environment env = {}
  );

  ~step() = default;

  static std::shared_ptr<step> create(
    std::shared_ptr<ctx> ctx,
    fs::path exe,
    arguments args = {},
    environment env = {}
  );

  std::shared_ptr<step> get();

  const arguments& options() const;

  std::shared_ptr<step> add_option(std::string opt);
  std::shared_ptr<step> add_options(arguments opts);

  const environment& env() const;

  std::shared_ptr<step> add_env(env::key key, env::value value);

  std::shared_ptr<step> depends_on(std::shared_ptr<step> other);
  std::shared_ptr<step> install();

  bool is_done() const;

private:
  int exec();

  friend ctx;

private:
  std::shared_ptr<ctx> m_ctx;

  fs::path m_exe;
  arguments m_args;
  environment m_env;

  int m_rc = RC_NOT_EXEC;

  std::vector<std::shared_ptr<step>> m_pre;
};
}

#endif
