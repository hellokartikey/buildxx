#ifndef BUILDXX_EXECUTABLE_HPP
#define BUILDXX_EXECUTABLE_HPP

#include "target.hpp"

namespace buildxx {
class executable : public target, public toolchain {
public:
  executable(build_ctx& ctx, const string& name);
  ~executable() override = default;

  const path& out_file() const override;

  executable& build_steps() override;

private:
  path m_out_file;
};
} // namespace buildxx

#endif
