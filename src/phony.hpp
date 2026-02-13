#ifndef HK_BUILDXX_PHONY_HPP
#define HK_BUILDXX_PHONY_HPP

#include "target.hpp"

namespace buildxx {
class build_ctx;

class phony : public target {
public:
  phony(build_ctx& ctx, std::string name);
  ~phony() override = default;

private:
  void create_steps(build_ctx& ctx, toolchain& tc) override;
};
} // namespace buildxx

#endif
