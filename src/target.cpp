#include "buildxx/target.hpp"

#include "buildxx/build_ctx.hpp"
#include "buildxx/shell.hpp"

namespace buildxx {
target::target(const string& name)
    : m_name(name)
    , m_first_step(&build().step())
    , m_link_step(&build().step()) {}

const string& target::name() const { return m_name; }

shell& target::first_step() { return *m_first_step; }

shell& target::final_step() { return *m_link_step; }

const vector<path>& target::files() const { return m_files; }
} // namespace buildxx
