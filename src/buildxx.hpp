#ifndef HK_BUILDXX_BUILDXX_HPP
#define HK_BUILDXX_BUILDXX_HPP

#include "build_ctx.hpp"
#include "toolchain.hpp"

#include "command.hpp"
#include "executable.hpp"
#include "library.hpp"
#include "phony.hpp"
#include "step.hpp"

namespace buildxx {
void build(build_ctx& ctx, toolchain& tc);
}

#endif
