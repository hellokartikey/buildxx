#include "phony.hpp"

#include "build_ctx.hpp"

namespace buildxx {
phony::phony(build_ctx& ctx, std::string name)
    : target(ctx, name) {}

void phony::create_steps(build_ctx& ctx, toolchain& tc) {}
} // namespace buildxx
