#include "target.hpp"

#include "build_ctx.hpp"

namespace buildxx {
target::target(build_ctx& ctx)
    : m_first_step(&ctx.add_phony())
    , m_final_step(&ctx.add_phony()) {
  final_step().depends_on(first_step());
}

step& target::first_step() { return *m_first_step; }

step& target::final_step() { return *m_final_step; }
} // namespace buildxx
