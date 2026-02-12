#include "build_ctx.hpp"

#include <print>
#include <stdexcept>

#include <spdlog/spdlog.h>

#include "phony.hpp"
#include "unix_toolchain.hpp"

namespace buildxx {
build_ctx::build_ctx()
    : m_tc(new unix_toolchain) {
  auto& install = phony::add(*this, INSTALL);
  install_step(install.final_step());
}

cli& build_ctx::cli() { return m_app; }

toolchain& build_ctx::toolchain() { return *m_tc; }

asio::io_context& build_ctx::io_context() { return m_io; }

build_ctx& build_ctx::install(target& target) {
  m_targets.front()->depends_on(target);
  return *this;
}

fs::path build_ctx::sub_directory(std::string f) const {
  auto path = directory() / f;

  if (!fs::exists(path) or !fs::is_directory(path)) {
    throw std::runtime_error(std::format("directory {} does not exist", f));
  }

  return fs::path{f};
}

fs::path build_ctx::prefix() const {
  auto path = directory() / PREFIX;

  create_if_not_exists(path);

  return path;
}

fs::path build_ctx::directory() const { return fs::current_path(); }

fs::path build_ctx::bin() const {
  auto path = prefix() / BIN_DIR;

  create_if_not_exists(path);

  return path;
}

fs::path build_ctx::tmp() const {
  auto path = prefix() / TMP_DIR;

  create_if_not_exists(path);

  return path;
}

step& build_ctx::add_step(fs::path exe,
                          step::arguments args,
                          step::environment_map env) {
  return m_steps.emplace_front(exe, args, env);
}

step& build_ctx::add_phony() {
  return m_steps.emplace_front(env::find_executable("true"));
}

void build_ctx::create_if_not_exists(fs::path path) const {
  if (!fs::exists(path)) {
    fs::create_directory(path);
  }
}

void build_ctx::build_install_steps() {
  m_targets.front()->create_steps_with_deps(*this, *m_tc);
  for (auto& step : m_install) {
    step->run(*this);
  }
}

void build_ctx::list_targets() const {
  using namespace std::ranges::views;

  for (const auto& [idx, ptr] : enumerate(m_targets)) {
    if (idx == 0) {
      std::println("{} [default]", ptr->name());
    } else {
      std::println("{}", ptr->name());
    }
  }
}

void build_ctx::install_step(step& step) { m_install.push_back(&step); }
} // namespace buildxx
