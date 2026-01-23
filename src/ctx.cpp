#include "ctx.hpp"

#include <stdexcept>

#include "unix_toolchain.hpp"

namespace bxx {
ctx::ctx(private_tag)
  : m_tc(std::make_shared<unix_toolchain>())
  , m_io(std::make_shared<asio::io_context>())
  {}

std::shared_ptr<ctx> ctx::create() {
  return std::make_shared<ctx>(ctx::private_tag{});
}

std::shared_ptr<ctx> ctx::get() {
  return shared_from_this();
}

fs::path ctx::sub_directory(std::string dir) const {
  auto path = fs::current_path() / dir;

  if (! fs::exists(path) or ! fs::is_directory(path)) {
    throw std::logic_error("Directory does not exist");
  }

  return path;
}

std::shared_ptr<toolchain> ctx::toolchain() { return m_tc; }

std::shared_ptr<asio::io_context> ctx::executor() { return m_io; }

std::shared_ptr<command> ctx::add_command(std::string exe, step::arguments args, step::environment env) {
  auto ptr = command::create(get(), exe, args, env);
  m_targets.emplace_back(ptr);
  return ptr;
}

std::shared_ptr<step> ctx::add_step(fs::path exe, step::arguments args, step::environment env) {
  m_steps.emplace_back(step::create(get(), exe, args, env));
  return m_steps.back();
}

std::shared_ptr<ctx> ctx::build() {
  for (auto& step : m_install) {
    step->exec();
  }

  return get();
}

void ctx::install_step(std::shared_ptr<step> step) {
  m_install.push_back(step);
}
}
