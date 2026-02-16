#ifndef HK_BUILDXX_BUILDXX_HPP
#define HK_BUILDXX_BUILDXX_HPP

#include "build_ctx.hpp"
#include "toolchain.hpp"

#include "command.hpp"    // IWYU pragma: export
#include "executable.hpp" // IWYU pragma: export
#include "library.hpp"    // IWYU pragma: export
#include "phony.hpp"      // IWYU pragma: export

namespace buildxx {
void build(build_ctx& ctx, toolchain& tc);
}

#endif
