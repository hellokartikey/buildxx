#ifndef HK_BUILDXX_CTX_HPP
#define HK_BUILDXX_CTX_HPP

#include <memory>
#include <vector>

#include "cli.hpp"
#include "cmd.hpp"
#include "exe.hpp"
#include "step.hpp"
#include "tc.hpp"

int main(int, char**);

namespace bxx {
class ctx : public std::enable_shared_from_this<ctx> {
private:
  struct private_tag {};

  static constexpr auto* CACHE = ".buildxx";
  static constexpr auto* PREFIX = "buildxx-out";

  static constexpr auto* BIN_DIR = "bin";
  static constexpr auto* LIB_DIR = "lib";

public:
  ctx(private_tag, std::shared_ptr<cli> cli);
  ~ctx() = default;

  std::shared_ptr<cli> cli();
  std::shared_ptr<tc> tc();
  std::shared_ptr<asio::io_context> exec();

  fs::path dir() const;
  fs::path prefix() const;
  fs::path cache() const;

  fs::path bin() const;

  fs::path sub_dir(std::string f) const;

  std::shared_ptr<step>
  add_step(fs::path exe, step::argv args = {}, step::env_map env = {});

  std::shared_ptr<cmd>
  add_cmd(std::string exe, step::argv args = {}, step::env_map env = {});

  std::shared_ptr<exe> add_exe(std::string bin, fs::path entry);

private:
  friend step;

  friend int ::main(int, char**);

  static std::shared_ptr<ctx> create(std::shared_ptr<bxx::cli> cli);
  std::shared_ptr<ctx> get();

private:
  void create_if_not_exists(fs::path path) const;

  std::shared_ptr<ctx> build();

  void install_step(std::shared_ptr<step> step);

private:
  std::shared_ptr<bxx::cli> m_app;

  std::shared_ptr<bxx::tc> m_tc;
  std::shared_ptr<asio::io_context> m_io;

  std::vector<std::shared_ptr<target>> m_targets;

  std::vector<std::shared_ptr<step>> m_steps;
  std::vector<std::shared_ptr<step>> m_install;
};
} // namespace bxx

#endif
