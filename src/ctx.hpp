#ifndef HK_BUILDXX_CTX_HPP
#define HK_BUILDXX_CTX_HPP

#include <memory>
#include <vector>

#include "command.hpp"
#include "executable.hpp"
#include "step.hpp"
#include "toolchain.hpp"

int main(int, char**);

namespace bxx {
class cli;

class ctx : public std::enable_shared_from_this<ctx> {
private:
  friend step;

  friend command;
  friend executable;

  friend int ::main(int, char**);

  struct private_tag {};

  static std::shared_ptr<ctx> create(std::shared_ptr<cli> cli);
  std::shared_ptr<ctx> get();

  static constexpr auto* CACHE = ".buildxx";
  static constexpr auto* PREFIX = "buildxx-out";

public:
  ctx(private_tag, std::shared_ptr<cli> cli);
  ~ctx() = default;

  std::shared_ptr<cli> cli();
  std::shared_ptr<toolchain> toolchain();
  std::shared_ptr<asio::io_context> executor();

  fs::path current_directory() const;
  fs::path prefix_directory() const;
  fs::path cache_directory() const;

  fs::path binary_directory() const;

  fs::path sub_directory(std::string dir) const;

  std::shared_ptr<command> add_command(std::string exe,
                                       step::arguments args = {},
                                       step::environment env = {});

  std::shared_ptr<executable> add_executable(std::string bin, fs::path entry);

private:
  void create_if_not_exists(fs::path path) const;

  std::shared_ptr<ctx> build();

  std::shared_ptr<step>
  add_step(fs::path exe, step::arguments args = {}, step::environment env = {});

  void install_step(std::shared_ptr<step> step);

  std::shared_ptr<ctx> set_verbose(bool v = true);

private:
  std::shared_ptr<bxx::cli> m_app;

  std::shared_ptr<bxx::toolchain> m_tc;
  std::shared_ptr<asio::io_context> m_io;

  std::vector<std::shared_ptr<target>> m_targets;

  std::vector<std::shared_ptr<step>> m_steps;
  std::vector<std::shared_ptr<step>> m_install;

  bool m_verbose;
};
} // namespace bxx

#endif
