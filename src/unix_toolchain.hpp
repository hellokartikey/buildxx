#include <string>

#include "toolchain.hpp"

using namespace std::literals;

namespace bxx {
class unix_toolchain : public toolchain {
public:
  unix_toolchain(std::string prefix = ""s);
  ~unix_toolchain() override = default;

  inline const fs::path& cxx() const override { return m_cxx; }
  inline const fs::path& cc() const override { return m_cc; }
  inline const fs::path& ld() const override { return m_ld; }

private:
  fs::path m_cc;
  fs::path m_cxx;
  fs::path m_ld;
};
}
