#include "toolchain.hpp"

namespace buildxx {
step::arguments toolchain::cxx_options(step::arguments options) {
  auto copy = m_cxx_opts;
  copy.append_range(std::move(options));
  return copy;
}
} // namespace buildxx
