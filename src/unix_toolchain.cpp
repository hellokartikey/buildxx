#include "unix_toolchain.hpp"

namespace bxx {
unix_toolchain::unix_toolchain(std::string prefix) {
  m_cxx = env::find_executable(prefix + "c++");
  m_cc = env::find_executable(prefix + "cc");
  m_ld = env::find_executable(prefix + "ld");
}
}
