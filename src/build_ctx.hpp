#ifndef HK_BUILDXX_BUILD_CTX_HPP
#define HK_BUILDXX_BUILD_CTX_HPP

#include <list>
#include <ranges>
#include <vector>

#include "cli.hpp"
#include "common.hpp"
#include "step.hpp"
#include "target.hpp"
#include "toolchain.hpp"

int main(int, char**);

namespace buildxx {
class build_ctx {
private:
  static constexpr auto* PREFIX = "buildxx-out";

  static constexpr auto* TMP_DIR = "tmp";
  static constexpr auto* BIN_DIR = "bin";
  static constexpr auto* LIB_DIR = "lib";

  build_ctx();
  friend int ::main(int, char**);

public:
  ~build_ctx() = default;

  toolchain& toolchain();
  asio::io_context& io_context();

  build_ctx& install(target& target);

  fs::path prefix() const;
  fs::path directory() const;
  fs::path sub_directory(std::string directory) const;

  fs::path bin() const;
  fs::path lib() const;
  fs::path tmp() const;

  step& add_step(fs::path exe, step::arguments args, step::environment_map env);
  step& add_phony();
  void install_step(step& step);

  template <std::derived_from<target> T> T& add_target(T* ptr) {
    using namespace std::ranges;

    if (contains(m_targets, ptr->name(),
                 [](auto& ptr) { return ptr->name(); })) {
      throw std::runtime_error(
          std::format("target with name {} already exists.", ptr->name()));
    }
    m_targets.emplace_back(ptr);
    return *ptr;
  }

private:
  void create_if_not_exists(fs::path path) const;

  target& find_target(std::string name);
  int build_install_steps(std::string name, bool verbose = false);
  int list_targets() const;

private:
  std::unique_ptr<buildxx::toolchain> m_tc;
  asio::io_context m_io;

  std::vector<std::unique_ptr<target>> m_targets;
  std::list<step> m_steps;
  std::vector<step*> m_install;
};
} // namespace buildxx

#endif
