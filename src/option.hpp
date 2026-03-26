#ifndef BUILDXX_OPTION_HPP
#define BUILDXX_OPTION_HPP

#include "types.hpp"

namespace buildxx {
template <typename T> class option {
public:
  option() = default;
  ~option() = default;

  option(const T& value)
      : m_value(value)
      , m_is_set(true) {}

  bool is_set() const { return m_is_set; }

  option& set(const T& value) {
    m_value = value;
    m_is_set = true;
    return *this;
  }

  const T& value() const {
    if (not is_set())
      throw error{"option not set"};
    return m_value;
  }

  T& value() {
    if (not is_set())
      throw error{"option not set"};
    return m_value;
  }

  T value_or(const T& def) const {
    if (is_set())
      return m_value;
    return def;
  }

  option& operator=(const T& value) { return set(value); }

  T& operator*() { return value(); }

  const T& operator*() const { return value(); }

  operator bool() const { return is_set(); }

  friend T operator or(const option& op, const T& def) {
    return op.value_or(def);
  }

private:
  T m_value;
  bool m_is_set = false;
};
} // namespace buildxx

#endif
