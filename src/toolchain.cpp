#include "toolchain.hpp"

namespace buildxx {
step::arguments toolchain::cxx_options(step::arguments options) {
  auto copy = m_cxx_opts;
  copy.append_range(options);
  return copy;
}

step::arguments toolchain::ar_options(step::arguments options) {
  auto copy = m_ar_opts;
  copy.append_range(options);
  return copy;
}
} // namespace buildxx
