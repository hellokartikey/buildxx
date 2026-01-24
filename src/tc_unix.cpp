#include "tc_unix.hpp"

namespace bxx {
tc_unix::tc_unix(private_tag, std::string prefix)
    : tc(private_tag{}) {
  m_cxx = env::find_executable(prefix + "c++");
  m_cc = env::find_executable(prefix + "cc");
  m_ld = env::find_executable(prefix + "ld");
}

ptr<tc_unix> tc_unix::create(std::string prefix) {
  return std::make_shared<tc_unix>(private_tag{}, prefix);
}
} // namespace bxx
