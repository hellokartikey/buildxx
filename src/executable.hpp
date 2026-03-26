#ifndef BUILDXX_EXECUTABLE_HPP
#define BUILDXX_EXECUTABLE_HPP

#include "target.hpp"

namespace buildxx {
class executable : public target {
public:
  executable(build_ctx& ctx, const string& name);
  ~executable() override = default;

  shell& first_step() override;
  shell& final_step() override;

  const path& out_file() const override;

  executable& build_steps() override;

private:
  path m_out_file;

  shell* m_link_step;
  shell* m_first_step;
};
} // namespace buildxx

#endif
