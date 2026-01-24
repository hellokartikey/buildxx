#include "tc.hpp"

namespace bxx {
ptr<tc> tc::add_cxx_opt(std::string opt) {
  m_cxx_opts.emplace_back(std::move(opt));
  return get();
}

ptr<tc> tc::add_cc_opt(std::string opt) {
  m_cc_opts.emplace_back(std::move(opt));
  return get();
}

ptr<tc> tc::add_ld_opt(std::string opt) {
  m_ld_opts.emplace_back(std::move(opt));
  return get();
}

ptr<tc> tc::add_cxx_opt(std::vector<std::string> opts) {
  for (auto& opt : opts) {
    add_cxx_opt(std::move(opt));
  }

  return get();
}

ptr<tc> tc::add_cc_opt(std::vector<std::string> opts) {
  for (auto& opt : opts) {
    add_cc_opt(std::move(opt));
  }

  return get();
}

ptr<tc> tc::add_ld_opt(std::vector<std::string> opts) {
  for (auto& opt : opts) {
    add_ld_opt(std::move(opt));
  }

  return get();
}

std::vector<std::string>
tc::cxx_opts(std::vector<std::string> extra_opts) const {
  auto copy = m_cxx_opts;

  for (auto& opt : extra_opts) {
    copy.emplace_back(std::move(opt));
  }

  return copy;
}

std::vector<std::string>
tc::cc_opts(std::vector<std::string> extra_opts) const {
  auto copy = m_cc_opts;

  for (auto& opt : extra_opts) {
    copy.emplace_back(std::move(opt));
  }

  return copy;
}

std::vector<std::string>
tc::ld_opts(std::vector<std::string> extra_opts) const {
  auto copy = m_ld_opts;

  for (auto& opt : extra_opts) {
    copy.emplace_back(std::move(opt));
  }

  return copy;
}
} // namespace bxx
