#ifndef HK_BUILDXX_UNIX_TOOLCHAIN_HPP
#define HK_BUILDXX_UNIX_TOOLCHAIN_HPP

#include <string>

#include "common.hpp"
#include "toolchain.hpp"

using namespace std::literals;

namespace buildxx {
class unix_toolchain : public toolchain {
public:
  unix_toolchain(std::string prefix = ""s);
  ~unix_toolchain() override = default;

  object build_cxx(build_ctx& ctx, fs::path src) override;
  binary link_cxx(build_ctx& ctx, std::string name, objects objects) override;

private:
  fs::path m_cc;
  fs::path m_cxx;
  fs::path m_ld;
};
} // namespace buildxx

#endif
