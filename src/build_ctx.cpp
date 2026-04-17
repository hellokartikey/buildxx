#include "buildxx/build_ctx.hpp"

#include <spdlog/spdlog.h>

#include "buildxx/shell.hpp"
#include "buildxx/target.hpp"

namespace buildxx {
build_ctx::build_ctx(int argc, char** argv, string script)
    : m_build(&step())
    , m_argc(argc)
    , m_argv(argv)
    , m_script(script) {}

path build_ctx::root() const { return m_root; }

path build_ctx::dir(string dir) const { return m_root / dir; }

path build_ctx::prefix() const { return m_prefix; }

path build_ctx::bin() const { return m_prefix / m_bin; }

path build_ctx::lib() const { return m_prefix / m_lib; }

path build_ctx::tmp() const { return m_prefix / m_tmp; }

shell& build_ctx::step() { return m_steps.emplace_back(); }

int build_ctx::argc() const { return m_argc; }

char** build_ctx::argv() const { return m_argv; }

const string& build_ctx::build_script() const { return m_script; }

shell& build_ctx::build_step() {
  if (not m_steps_created) {
    for (auto& lib : m_targets) {
      lib->build_steps();
    }

    m_steps_created = true;
  }

  return *m_build;
}
} // namespace buildxx
