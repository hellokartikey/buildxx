#include "build_ctx.hpp"

#include <spdlog/spdlog.h>

#include "shell.hpp"

namespace buildxx {
build_ctx::build_ctx()
    : m_build(&step()) {}

path build_ctx::root() const { return m_root; }

path build_ctx::dir(string dir) const { return m_root / dir; }

path build_ctx::prefix() const { return m_prefix; }

path build_ctx::bin() const { return m_prefix / m_bin; }

path build_ctx::lib() const { return m_prefix / m_lib; }

path build_ctx::tmp() const { return m_prefix / m_tmp; }

shell& build_ctx::step() { return m_steps.emplace_back(); }

shell& build_ctx::build_step() { return *m_build; }
} // namespace buildxx
