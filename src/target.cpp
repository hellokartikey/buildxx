#include "target.hpp"

namespace bxx {
target::target(private_tag, std::string name)
    : m_name(name) {}

ptr<target> target::create(std::string name) {
  return std::make_shared<target>(private_tag{}, name);
}

const std::string& target::name() const { return m_name; }

ptr<target> target::build() {
  build_pre();
  m_built = true;
  return get();
}

ptr<target> target::install() {
  for (auto tar : pre()) {
    tar->install();
  }

  m_installed = true;
  return get();
}

bool target::is_built() const { return m_built; }

bool target::is_installed() const { return m_installed; }
} // namespace bxx
