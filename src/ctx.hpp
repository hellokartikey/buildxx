#ifndef HK_BUILDXX_CTX_HPP
#define HK_BUILDXX_CTX_HPP

#include <memory>
#include <vector>

#include "command.hpp"
#include "toolchain.hpp"
#include "step.hpp"

namespace bxx {
class cli;

class ctx : public std::enable_shared_from_this<ctx> {
private:
  friend step;
  friend command;
  friend cli;

  struct private_tag {};

  static std::shared_ptr<ctx> create();
  std::shared_ptr<ctx> get();

public:
  ctx(private_tag);
  ~ctx() = default;

  std::shared_ptr<toolchain> toolchain();
  std::shared_ptr<asio::io_context> executor();

  fs::path sub_directory(std::string dir) const;

  std::shared_ptr<command> add_command(
    std::string exe,
    step::arguments args = {},
    step::environment env = {}
  );

private:
  std::shared_ptr<ctx> build();

  std::shared_ptr<step> add_step(
    fs::path exe,
    step::arguments args = {},
    step::environment env = {}
  );

  void install_step(std::shared_ptr<step> step);

private:
  std::shared_ptr<bxx::toolchain> m_tc;
  std::shared_ptr<asio::io_context> m_io;

  std::vector<std::shared_ptr<target>> m_targets;

  std::vector<std::shared_ptr<step>> m_steps;
  std::vector<std::shared_ptr<step>> m_install;
};
}

#endif
