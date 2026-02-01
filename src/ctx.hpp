#ifndef HK_BUILDXX_CTX_HPP
#define HK_BUILDXX_CTX_HPP

#include <memory>
#include <vector>

#include "cli.hpp"
#include "cmd.hpp"
#include "common.hpp"
#include "exe.hpp"
#include "step.hpp"
#include "tc.hpp"

int main(int, char**);

namespace bxx {
class ctx : public std::enable_shared_from_this<ctx> {
private:
  struct private_tag {};

  static constexpr auto* PREFIX = "buildxx-out";

  static constexpr auto* TMP_DIR = "tmp";
  static constexpr auto* BIN_DIR = "bin";
  static constexpr auto* LIB_DIR = "lib";

public:
  ctx(private_tag, ptr<cli> cli);
  ~ctx() = default;

  ptr<cli> cli();
  ptr<tc> tc();
  ptr<asio::io_context> exec();

  fs::path dir() const;
  fs::path prefix() const;
  fs::path cache() const;

  fs::path bin() const;

  fs::path sub_dir(std::string f) const;

  ptr<step>
  add_step(fs::path exe, step::argv args = {}, step::env_map env = {});

  ptr<cmd>
  add_cmd(std::string exe, step::argv args = {}, step::env_map env = {});

  ptr<exe> add_exe(std::string bin, fs::path entry);

private:
  friend step;

  friend int ::main(int, char**);

  static ptr<ctx> create(ptr<bxx::cli> cli);
  ptr<ctx> get();

private:
  void create_if_not_exists(fs::path path) const;

  ptr<ctx> build();

  void install_step(ptr<step> step);

private:
  ptr<bxx::cli> m_app;

  ptr<bxx::tc> m_tc;
  ptr<asio::io_context> m_io;

  std::vector<ptr<target>> m_targets;

  std::vector<ptr<step>> m_steps;
  std::vector<ptr<step>> m_install;
};
} // namespace bxx

#endif
