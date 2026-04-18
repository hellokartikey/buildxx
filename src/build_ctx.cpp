#include "buildxx/build_ctx.hpp"

#include <spdlog/spdlog.h>

#include "buildxx/cli_ctx.hpp"
#include "buildxx/shell.hpp"
#include "buildxx/target.hpp"

namespace buildxx {
build_ctx::build_ctx()
    : m_build(&step())
    , m_script(cli().script()) {}

build_ctx& build() {
  static build_ctx ctx;
  return ctx;
}

path build_ctx::root() const { return m_root; }

path build_ctx::dir(string dir) const { return m_root / dir; }

path build_ctx::prefix() const { return m_prefix; }

path build_ctx::bin() const { return m_prefix / m_bin; }

path build_ctx::lib() const { return m_prefix / m_lib; }

path build_ctx::tmp() const { return m_prefix / m_tmp; }

shell& build_ctx::step() { return m_steps.emplace_back(); }

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
