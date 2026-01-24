#ifndef HK_BUILDXX_TARGET_HPP
#define HK_BUILDXX_TARGET_HPP

#include <memory>

#include "common.hpp"
#include "step.hpp"
#include "tc.hpp"

namespace bxx {
class target : public std::enable_shared_from_this<target> {
protected:
  struct private_tag {};

  template <class T> ptr<T> build_pre(this T& self) {
    for (auto pre : self.m_pre) {
      if (!pre->is_built()) {
        pre->build();
      }
    }

    return self.get();
  }

  template <class T> ptr<T> get(this T& self) {
    return std::static_pointer_cast<T>(self.shared_from_this());
  }

  virtual ptr<target> build();

public:
  target(private_tag, std::string name);
  virtual ~target() = default;

  static ptr<target> create(std::string name);

  bool is_built() const;
  bool is_installed() const;

  virtual ptr<target> install();

  template <class T> ptr<T> depends_on(this T& self, ptr<target> other) {
    self.m_pre.push_back(other);
    return self.get();
  }

  template <class T>
  ptr<T> depends_on(this T& self, std::vector<ptr<target>> others) {
    for (auto other : others) {
      self.depends_on(other);
    }
    return self.get();
  }

  const std::string& name() const;

private:
  std::string m_name;
  std::vector<ptr<target>> m_pre;

  bool m_built = false;
  bool m_installed = false;
};
} // namespace bxx

#endif
