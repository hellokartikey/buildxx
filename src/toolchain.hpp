#ifndef HK_BUILDXX_TOOLCHAIN_HPP
#define HK_BUILDXX_TOOLCHAIN_HPP

#include "common.hpp"

namespace bxx {
class toolchain {
public:
  toolchain() = default;
  virtual ~toolchain() = default;

  virtual const fs::path& cxx() const = 0;
  virtual const fs::path& cc() const = 0;
  virtual const fs::path& ld() const = 0;

  toolchain& add_cxx_option(std::string opt);
  toolchain& add_cc_option(std::string opt);
  toolchain& add_ld_option(std::string opt);

  toolchain& add_cxx_options(std::vector<std::string> opts);
  toolchain& add_cc_options(std::vector<std::string> opts);
  toolchain& add_ld_options(std::vector<std::string> opts);

  std::vector<std::string>
  cxx_options(std::vector<std::string> extra_opts) const;
  std::vector<std::string>
  cc_options(std::vector<std::string> extra_opts) const;
  std::vector<std::string>
  ld_options(std::vector<std::string> extra_opts) const;

private:
  std::vector<std::string> m_cxx_opts;
  std::vector<std::string> m_cc_opts;
  std::vector<std::string> m_ld_opts;
};
} // namespace bxx

#endif
