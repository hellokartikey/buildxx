#include "target.hpp"

#include "build_ctx.hpp"

namespace buildxx {
target::target(build_ctx& ctx, std::string name)
    : m_name(name)
    , m_first_step(&ctx.add_phony())
    , m_final_step(&ctx.add_phony()) {}

const std::string& target::name() const { return m_name; }

void target::create_steps_with_deps(build_ctx& ctx, toolchain& tc) {
  if (m_steps_created) {
    return;
  }

  for (auto* dep : m_deps) {
    dep->create_steps_with_deps(ctx, tc);
  }

  final_step().depends_on_first(first_step());

  create_steps(ctx, tc);

  m_steps_created = true;
}

step& target::first_step() { return *m_first_step; }

step& target::final_step() { return *m_final_step; }
} // namespace buildxx
