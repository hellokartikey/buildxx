#include "ctx.hpp"

#include <stdexcept>

#include "unix_toolchain.hpp"

namespace bxx {
ctx::ctx() : m_tc(new unix_toolchain), m_io({}) {}

fs::path ctx::sub_directory(std::string dir) const {
  auto path = fs::current_path() / dir;

  if (! fs::exists(path) or ! fs::is_directory(path)) {
    throw std::logic_error("Directory does not exist");
  }

  return path;
}

step& ctx::add_step(fs::path exe, step::arguments args, step::environment env) {
  m_steps.emplace_back(std::make_unique<step>(*this, exe, args, env));
  return *(m_steps.back());
}

ctx& ctx::build() {
  for (auto& step : m_install) {
    step->exec();
  }

  return *this;
}

void ctx::install_step(step& step) {
  m_install.push_back(&step);
}
}
