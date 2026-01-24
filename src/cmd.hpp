#ifndef HK_BUILDXX_CMD_HPP
#define HK_BUILDXX_CMD_HPP

#include "step.hpp"
#include "target.hpp"

namespace bxx {
class ctx;

class cmd : public target {
public:
  cmd(private_tag,
      std::shared_ptr<ctx> ctx,
      std::string exe,
      step::argv args = {},
      step::env_map env = {});

  ~cmd() override = default;

  static std::shared_ptr<cmd> create(std::shared_ptr<ctx> ctx,
                                     std::string exe,
                                     step::argv args = {},
                                     step::env_map env = {});

  std::shared_ptr<target> install() override;

  const step::argv& opts() const;
  std::shared_ptr<cmd> add_opt(std::string opt);
  std::shared_ptr<cmd> add_opt(step::argv opts);

  const step::env_map& env() const;
  std::shared_ptr<cmd> add_env(env::key key, env::value value);

protected:
  std::shared_ptr<target> build() override;

private:
  std::shared_ptr<ctx> m_ctx;
  std::shared_ptr<step> m_step;
};
} // namespace bxx

#endif
