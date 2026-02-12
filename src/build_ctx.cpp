#include "build_ctx.hpp"

#include <stdexcept>
#include <print>

#include <spdlog/spdlog.h>

#include "unix_toolchain.hpp"

namespace buildxx {
build_ctx::build_ctx()
    : m_tc(new unix_toolchain) {}

cli& build_ctx::cli() { return m_app; }

toolchain& build_ctx::toolchain() { return *m_tc; }

asio::io_context& build_ctx::io_context() { return m_io; }

build_ctx& build_ctx::install(target& target) {
  target.create_steps_with_deps(*this, *m_tc);
  install_step(target.final_step());
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
  for (auto& step : m_install) {
    step->run(*this);
  }
}

void build_ctx::list_targets() const {
  for (const auto& [k, v] : m_targets) {
    std::println("{}", k);
  }
}

void build_ctx::install_step(step& step) { m_install.push_back(&step); }
} // namespace buildxx
