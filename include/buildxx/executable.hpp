#ifndef BUILDXX_EXECUTABLE_HPP
#define BUILDXX_EXECUTABLE_HPP

#include "target.hpp"

namespace buildxx {
class executable : public target, public toolchain {
public:
  executable(const string& name);
  ~executable() override = default;

  executable& out_file(const path& file) override;
  const path& out_file() const override;

  executable& build_steps() override;

  shell& run_step();

private:
  path m_out_file;
};
} // namespace buildxx

#endif
