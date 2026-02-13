#include "build_ctx.hpp"

#include <print>
#include <ranges>
#include <stdexcept>

#include <spdlog/spdlog.h>

#include "cli.hpp"
#include "phony.hpp"

namespace buildxx {
build_ctx::build_ctx() {
  auto& install = target<phony>(cli::INSTALL);
  install_step(install.final_step());
}

asio::io_context& build_ctx::io_context() { return m_io; }

build_ctx& build_ctx::install(class target& target) {
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

fs::path build_ctx::lib() const {
  auto path = prefix() / LIB_DIR;

  create_if_not_exists(path);

  return path;
}

fs::path build_ctx::tmp(fs::path p) const {
  auto path = prefix() / TMP_DIR / p;

  create_if_not_exists(path);

  return path;
}

step& build_ctx::add_step(fs::path exe,
                          step::arguments args,
                          step::environment_map env) {
  return m_steps.emplace_front(exe, args, env);
}

step& build_ctx::add_phony() { return m_steps.emplace_front("").phony(true); }

void build_ctx::create_if_not_exists(fs::path path) const {
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
}

target& build_ctx::find_target(std::string name) {
  using namespace std::ranges;

  auto iter = find(m_targets, name, [&](auto& ptr) { return ptr->name(); });
  if (iter == m_targets.end()) {
    throw std::runtime_error(std::format("target {} does not exist", name));
  }

  return *(*iter).get();
}

int build_ctx::build_install_steps(toolchain& tc,
                                   std::string name,
                                   bool verbose) {
  auto& build = find_target(name);
  build.create_steps_with_deps(*this, tc);
  return build.final_step().run(*this, verbose);
}

int build_ctx::list_targets() const {
  using namespace std::ranges::views;

  for (const auto& [idx, ptr] : enumerate(m_targets)) {
    if (idx == 0) {
      std::println("{} [default]", ptr->name());
    } else {
      std::println("{}", ptr->name());
    }
  }

  return 0;
}

void build_ctx::install_step(step& step) { m_install.push_back(&step); }
} // namespace buildxx
