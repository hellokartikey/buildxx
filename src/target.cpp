#include "target.hpp"

namespace bxx {
target::target(private_tag, std::string name) : m_name(name) {}

std::shared_ptr<target> target::create(std::string name) {
  return std::make_shared<target>(private_tag{}, name);
}

const std::string& target::name() const {
  return m_name;
}

std::shared_ptr<target> target::build(toolchain& tc) {
  build_pre(tc);
  m_built = true;
  return get();
}

std::shared_ptr<target> target::install() {
  m_installed = true;
  return get();
}

bool target::is_built() const {
  return m_built;
}

bool target::is_installed() const {
  return m_installed;
}
}
