#ifndef HK_BUILDXX_CMD_HPP
#define HK_BUILDXX_CMD_HPP

#include "common.hpp"
#include "step.hpp"
#include "target.hpp"

namespace bxx {
class ctx;

class cmd : public target {
public:
  cmd(private_tag,
      ptr<ctx> ctx,
      std::string exe,
      step::argv args = {},
      step::env_map env = {});

  ~cmd() override = default;

  static ptr<cmd> create(ptr<ctx> ctx,
                         std::string exe,
                         step::argv args = {},
                         step::env_map env = {});

  ptr<target> install() override;

  const step::argv& opts() const;
  ptr<cmd> add_opt(std::string opt);
  ptr<cmd> add_opt(step::argv opts);

  const step::env_map& env() const;
  ptr<cmd> add_env(env::key key, env::value value);

  const std::string& msg() const;
  ptr<cmd> add_msg(std::string msg);

protected:
  ptr<target> build() override;

private:
  ptr<ctx> m_ctx;
  ptr<step> m_step;
};
} // namespace bxx

#endif
