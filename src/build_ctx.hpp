#ifndef BUILDXX_BUILD_CTX_HPP
#define BUILDXX_BUILD_CTX_HPP

#include <concepts>

#include "option.hpp"
#include "types.hpp"

namespace buildxx {
class target;
class shell;

class build_ctx {
public:
  build_ctx() = default;
  ~build_ctx() = default;

  path root() const;
  path dir(string dir) const;

  path prefix() const;
  path bin() const;
  path lib() const;
  path tmp() const;

  template <std::derived_from<target> T> T& add(string name);

  shell& step();

  template <typename T> option<T> config(string name, string description);

private:
  path m_root = fs::current_path();
  path m_prefix = m_root / "buildxx-out";

  string m_bin = "bin";
  string m_lib = "lib";
  string m_tmp = "tmp";

  list<shell> m_steps;
};
} // namespace buildxx

#endif
