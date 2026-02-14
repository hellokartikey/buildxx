#ifndef HK_BUILDXX_BUILD_CTX_HPP
#define HK_BUILDXX_BUILD_CTX_HPP

#include <list>
#include <vector>

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
  static constexpr auto* INC_DIR = "include";

  build_ctx(std::string build_script);
  friend int ::main(int, char**);

public:
  ~build_ctx() = default;

  asio::io_context& io_context();

  build_ctx& install(class target& target);

  fs::path prefix() const;
  fs::path directory() const;
  fs::path sub_directory(std::string directory = "") const;

  fs::path bin() const;
  fs::path lib() const;
  fs::path tmp(fs::path path) const;

  step& add_step(fs::path exe, step::arguments args, step::environment_map env);
  step& add_phony();
  void install_step(step& step);

  template <class T>
    requires(std::derived_from<T, class target>)
  T& target(std::string name) {
    using namespace std::ranges;

    if (contains(m_targets, name, [](auto& ptr) { return ptr->name(); })) {
      throw std::runtime_error(
          std::format("target with name {} already exists.", name));
    }

    return static_cast<T&>(
        *m_targets.emplace_back(std::make_unique<T>(*this, name)));
  }

private:
  void create_if_not_exists(fs::path path) const;

  class target& find_target(std::string name);
  fs::path build_script(toolchain& tc, bool verbose = false);
  int build_install_steps(toolchain& tc,
                          std::string name,
                          bool verbose = false);
  int list_targets() const;

private:
  asio::io_context m_io;

  std::string m_build_script;

  std::vector<std::unique_ptr<class target>> m_targets;
  std::list<step> m_steps;
  std::vector<step*> m_install;
};
} // namespace buildxx

#endif
