#include "target.hpp"

namespace buildxx {
target::target(build_ctx& ctx, const string& name)
    : toolchain()
    , m_ctx(&ctx)
    , m_name(name) {}

const string& target::name() const { return m_name; }

const vector<path>& target::files() const { return m_files; }

build_ctx& target::ctx() { return *m_ctx; }
} // namespace buildxx
