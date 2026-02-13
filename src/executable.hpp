#ifndef HK_BUILDXX_EXECUTABLE_HPP
#define HK_BUILDXX_EXECUTABLE_HPP

#include "code.hpp"
#include "common.hpp"
#include "target.hpp"
#include "toolchain.hpp"

namespace buildxx {
class executable : public target, public code_mixin {
public:
  executable(build_ctx& ctx, std::string name);
  ~executable() override = default;

  const std::optional<binary>& artifact() const;

protected:
  void create_steps(build_ctx& ctx, toolchain& tc) override;

protected:
  std::optional<binary> m_binary;
  step* m_link_step{};

  std::vector<step*> m_obj_steps{};
};
} // namespace buildxx

#endif
