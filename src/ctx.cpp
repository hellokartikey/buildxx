#include "ctx.hpp"

#include <stdexcept>

#include <spdlog/spdlog.h>

#include "cli.hpp"
#include "tc_unix.hpp"

namespace bxx {
ctx::ctx(private_tag, ptr<bxx::cli> cli)
    : m_app(cli)
    , m_tc(tc_unix::create())
    , m_io(std::make_shared<asio::io_context>()) {}

ptr<ctx> ctx::create(ptr<bxx::cli> cli) {
  return std::make_shared<ctx>(ctx::private_tag{}, cli);
}

ptr<ctx> ctx::get() { return shared_from_this(); }

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
  auto path = prefix() / TMP_DIR;

  create_if_not_exists(path);

  return path;
}

ptr<cli> ctx::cli() { return m_app; }

ptr<tc> ctx::tc() { return m_tc; }

ptr<asio::io_context> ctx::exec() { return m_io; }

ptr<cmd> ctx::add_cmd(std::string exe, step::argv args, step::env_map env) {
  auto ptr = cmd::create(get(), exe, args, env);
  m_targets.emplace_back(ptr);
  return ptr;
}

ptr<exe> ctx::add_exe(std::string bin, fs::path entry) {
  auto ptr = exe::create(get(), bin, entry);
  m_targets.emplace_back(ptr);
  return ptr;
}

ptr<step> ctx::add_step(fs::path exe, step::argv args, step::env_map env) {
  m_steps.emplace_back(step::create(get(), exe, args, env));
  return m_steps.back();
}

void ctx::create_if_not_exists(fs::path path) const {
  if (!fs::exists(path)) {
    fs::create_directory(path);
  }
}

ptr<ctx> ctx::build() {
  try {
    for (auto& step : m_install) {
      bxx::exec(step);
    }
  } catch (std::runtime_error& e) {
    spdlog::critical("error: {}", e.what());
  }

  return get();
}

void ctx::install_step(ptr<step> step) { m_install.push_back(step); }
} // namespace bxx
