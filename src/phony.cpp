#include "phony.hpp"

#include "build_ctx.hpp"

namespace buildxx {
phony::phony(build_ctx& ctx, std::string name)
    : target(ctx, name) {}

phony& phony::add(build_ctx& ctx, std::string name) {
  return ctx.add_target(new phony(ctx, name));
}

void phony::create_steps(build_ctx& ctx, toolchain& tc) {}
} // namespace buildxx
