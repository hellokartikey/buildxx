#include <buildxx/buildxx.hpp>

namespace buildxx {
target::target(build_ctx& ctx, const string& name)
    : m_ctx(&ctx)
    , m_name(name)
    , m_first_step(&ctx.step())
    , m_link_step(&ctx.step()) {}

const string& target::name() const { return m_name; }

shell& target::first_step() { return *m_first_step; }

shell& target::final_step() { return *m_link_step; }

const vector<path>& target::files() const { return m_files; }

build_ctx& target::ctx() { return *m_ctx; }

const build_ctx& target::ctx() const { return *m_ctx; }
} // namespace buildxx
