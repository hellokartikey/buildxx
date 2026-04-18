#ifndef BUILDXX_BUILD_CTX_HPP
#define BUILDXX_BUILD_CTX_HPP

#include <concepts>

#include "option.hpp"
#include "types.hpp"

namespace buildxx {
class shell;
class target;

class build_ctx;
build_ctx& build();

class build_ctx {
  build_ctx();
  ~build_ctx() = default;

public:
  friend build_ctx& build();

  path root() const;
  path dir(string dir) const;

  path prefix() const;
  path bin() const;
  path lib() const;
  path tmp() const;

  template <std::derived_from<target> T> T& add(const string& name) {
    auto* ptr = new T(name);
    m_targets.emplace_back(ptr);
    return *ptr;
  }

  shell& step();
  shell& build_step();

  const string& build_script() const;

  template <typename T> option<T> config(string name, string description);

private:
  path m_root = fs::relative(fs::current_path());
  path m_prefix = m_root / "buildxx-out";

  string m_bin = "bin";
  string m_lib = "lib";
  string m_tmp = ".cache";

  list<shell> m_steps;
  vector<std::unique_ptr<target>> m_targets;

  shell* m_build = nullptr;

  bool m_steps_created = false;

  string m_script;
};
} // namespace buildxx

#endif
