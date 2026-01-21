#include "toolchain.hpp"

namespace bxx::tc {
toolchain& toolchain::add_cxx_option(std::string opt) {
  m_cxx_opts.emplace_back(std::move(opt));
  return *this;
}

toolchain& toolchain::add_cc_option(std::string opt) {
  m_cc_opts.emplace_back(std::move(opt));
  return *this;
}

toolchain& toolchain::add_ld_option(std::string opt) {
  m_ld_opts.emplace_back(std::move(opt));
  return *this;
}

toolchain& toolchain::add_cxx_options(std::vector<std::string> opts) {
  for (auto& opt : opts) {
    add_cxx_option(std::move(opt));
  }

  return *this;
}

toolchain& toolchain::add_cc_options(std::vector<std::string> opts) {
  for (auto& opt : opts) {
    add_cc_option(std::move(opt));
  }

  return *this;
}

toolchain& toolchain::add_ld_options(std::vector<std::string> opts) {
  for (auto& opt : opts) {
    add_ld_option(std::move(opt));
  }

  return *this;
}

std::vector<std::string> toolchain::cxx_options(std::vector<std::string> extra_opts) const {
  auto copy = m_cxx_opts;

  for (auto& opt : extra_opts) {
    copy.emplace_back(std::move(opt));
  }

  return copy;
}

std::vector<std::string> toolchain::cc_options(std::vector<std::string> extra_opts) const {
  auto copy = m_cc_opts;

  for (auto& opt : extra_opts) {
    copy.emplace_back(std::move(opt));
  }

  return copy;
}

std::vector<std::string> toolchain::ld_options(std::vector<std::string> extra_opts) const {
  auto copy = m_ld_opts;

  for (auto& opt : extra_opts) {
    copy.emplace_back(std::move(opt));
  }

  return copy;
}
}
