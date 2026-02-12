#ifndef HK_BUILDXX_PHONY_HPP
#define HK_BUILDXX_PHONY_HPP

#include "target.hpp"

namespace buildxx {
class build_ctx;

class phony : public target {
  phony(build_ctx& ctx, std::string name);

public:
  ~phony() override = default;

  static phony& add(build_ctx& ctx, std::string name);

  void create_steps(build_ctx& ctx, toolchain& tc) override;
};
} // namespace buildxx

#endif
