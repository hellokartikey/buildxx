#ifndef HK_BUILDXX_COMMAND_HPP
#define HK_BUILDXX_COMMAND_HPP

#include "target.hpp"
#include "step.hpp"

namespace bxx {
class ctx;

class command : public target {
protected:
  struct private_tag {};

public:
  command(
    private_tag,
    std::shared_ptr<ctx> ctx,
    std::string exe,
    step::arguments args = {},
    step::environment env = {}
  );

  ~command() override = default;

  static std::shared_ptr<command> create(
    std::shared_ptr<ctx> ctx,
    std::string exe,
    step::arguments args = {},
    step::environment env = {}
  );

  std::shared_ptr<target> install() override;

  const step::arguments& options() const;
  std::shared_ptr<command> add_option(std::string opt);
  std::shared_ptr<command> add_options(step::arguments opts);

  const step::environment& env() const;
  std::shared_ptr<command> add_env(env::key key, env::value value);

protected:
  std::shared_ptr<target> build(toolchain& tc) override;

private:
  std::shared_ptr<ctx> m_ctx;
  std::shared_ptr<step> m_step;
};
}

#endif
