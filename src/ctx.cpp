#include "ctx.hpp"

#include <print>
#include <stdexcept>

#include "cli.hpp"
#include "unix_toolchain.hpp"

namespace bxx {
ctx::ctx(private_tag, std::shared_ptr<bxx::cli> cli)
    : m_app(cli)
    , m_tc(std::make_shared<unix_toolchain>())
    , m_io(std::make_shared<asio::io_context>()) {}

std::shared_ptr<ctx> ctx::create(std::shared_ptr<bxx::cli> cli) {
  return std::make_shared<ctx>(ctx::private_tag{}, cli);
}

std::shared_ptr<ctx> ctx::get() { return shared_from_this(); }

fs::path ctx::current_directory() const { return fs::current_path(); }

fs::path ctx::sub_directory(std::string dir) const {
  auto path = current_directory() / dir;

  if (!fs::exists(path) or !fs::is_directory(path)) {
    throw std::logic_error("Directory does not exist");
  }

  return fs::path{dir};
}

fs::path ctx::prefix_directory() const {
  auto path = current_directory() / PREFIX;

  create_if_not_exists(path);

  return path;
}

fs::path ctx::binary_directory() const {
  auto path = prefix_directory() / "bin";

  create_if_not_exists(path);

  return path;
}

fs::path ctx::cache_directory() const {
  auto path = current_directory() / CACHE;

  create_if_not_exists(path);

  return path;
}

std::shared_ptr<cli> ctx::cli() { return m_app; }

std::shared_ptr<toolchain> ctx::toolchain() { return m_tc; }

std::shared_ptr<asio::io_context> ctx::executor() { return m_io; }

std::shared_ptr<command>
ctx::add_command(std::string exe, step::arguments args, step::environment env) {
  auto ptr = command::create(get(), exe, args, env);
  m_targets.emplace_back(ptr);
  return ptr;
}

std::shared_ptr<executable> ctx::add_executable(std::string bin,
                                                fs::path entry) {
  auto ptr = executable::create(get(), bin, entry);
  m_targets.emplace_back(ptr);
  return ptr;
}

std::shared_ptr<step>
ctx::add_step(fs::path exe, step::arguments args, step::environment env) {
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
      step->exec();
    }
  } catch (std::runtime_error& e) {
    std::println(stderr, "error: {}", e.what());
  }

  return get();
}

void ctx::install_step(std::shared_ptr<step> step) {
  m_install.push_back(step);
}

std::shared_ptr<ctx> ctx::set_verbose(bool v) {
  m_verbose = v;
  return get();
}
} // namespace bxx
