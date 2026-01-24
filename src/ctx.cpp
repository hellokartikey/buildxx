#include "ctx.hpp"

#include <print>
#include <stdexcept>

#include "cli.hpp"
#include "tc_unix.hpp"

namespace bxx {
ctx::ctx(private_tag, std::shared_ptr<bxx::cli> cli)
    : m_app(cli)
    , m_tc(tc_unix::create())
    , m_io(std::make_shared<asio::io_context>()) {}

std::shared_ptr<ctx> ctx::create(std::shared_ptr<bxx::cli> cli) {
  return std::make_shared<ctx>(ctx::private_tag{}, cli);
}

std::shared_ptr<ctx> ctx::get() { return shared_from_this(); }

fs::path ctx::dir() const { return fs::current_path(); }

fs::path ctx::sub_dir(std::string f) const {
  auto path = dir() / f;

  if (!fs::exists(path) or !fs::is_directory(path)) {
    throw std::runtime_error("directory does not exist");
  }

  return fs::path{f};
}

fs::path ctx::prefix() const {
  auto path = dir() / PREFIX;

  create_if_not_exists(path);

  return path;
}

fs::path ctx::bin() const {
  auto path = prefix() / BIN_DIR;

  create_if_not_exists(path);

  return path;
}

fs::path ctx::cache() const {
  auto path = dir() / CACHE;

  create_if_not_exists(path);

  return path;
}

std::shared_ptr<cli> ctx::cli() { return m_app; }

std::shared_ptr<tc> ctx::tc() { return m_tc; }

std::shared_ptr<asio::io_context> ctx::exec() { return m_io; }

std::shared_ptr<cmd>
ctx::add_cmd(std::string exe, step::argv args, step::env_map env) {
  auto ptr = cmd::create(get(), exe, args, env);
  m_targets.emplace_back(ptr);
  return ptr;
}

std::shared_ptr<exe> ctx::add_exe(std::string bin, fs::path entry) {
  auto ptr = exe::create(get(), bin, entry);
  m_targets.emplace_back(ptr);
  return ptr;
}

std::shared_ptr<step>
ctx::add_step(fs::path exe, step::argv args, step::env_map env) {
  m_steps.emplace_back(step::create(get(), exe, args, env));
  return m_steps.back();
}

void ctx::create_if_not_exists(fs::path path) const {
  if (!fs::exists(path)) {
    fs::create_directory(path);
  }
}

std::shared_ptr<ctx> ctx::build() {
  try {
    for (auto& step : m_install) {
      bxx::exec(step);
    }
  } catch (std::runtime_error& e) {
    std::println(stderr, "error: {}", e.what());
  }

  return get();
}

void ctx::install_step(std::shared_ptr<step> step) {
  m_install.push_back(step);
}
} // namespace bxx
