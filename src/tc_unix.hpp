#include <string>

#include "common.hpp"
#include "tc.hpp"

using namespace std::literals;

namespace bxx {
class tc_unix : public tc {
public:
  tc_unix(private_tag, std::string prefix = ""s);
  ~tc_unix() override = default;

  static ptr<tc_unix> create(std::string prefix = ""s);

  inline const fs::path& cxx() const override { return m_cxx; }
  inline const fs::path& cc() const override { return m_cc; }
  inline const fs::path& ld() const override { return m_ld; }

private:
  fs::path m_cc;
  fs::path m_cxx;
  fs::path m_ld;
};
} // namespace bxx
