#include "toolchain.hpp"

#include <ranges>

#include <spdlog/spdlog.h>

#include "library.hpp"

namespace buildxx {
toolchain::toolchain()
    : m_cxx(env::find_executable("c++"))
    , m_cc(env::find_executable("cc"))
    , m_ld(env::find_executable("ld"))
    , m_ar(env::find_executable("ar")) {}

int toolchain::std() const { return m_std; }

bool toolchain::c_lang() const { return m_c; }

bool toolchain::shared() const { return m_shared; }

const path& toolchain::cxx() const { return m_cxx; }

const path& toolchain::cc() const { return m_cc; }

const path& toolchain::ld() const { return m_ld; }

const path& toolchain::ar() const { return m_ar; }

const vector<path>& toolchain::includes() const { return m_includes; }

const map<string, string>& toolchain::defines() const { return m_defines; }

const vector<string>& toolchain::undefines() const { return m_undefines; }

const vector<string>& toolchain::cxx_flags() const { return m_cxx_flags; }

const vector<string>& toolchain::cc_flags() const { return m_cc_flags; }

const vector<string>& toolchain::ar_flags() const { return m_ar_flags; }

const vector<string>& toolchain::ld_flags() const { return m_ld_flags; }

vector<library*> toolchain::link_libraries() const { return m_link; }

vector<string> toolchain::build_flags() const {
  namespace views = std::views;
  namespace ranges = std::ranges;

  vector<string> tc_flags;

  if (c_lang()) {
    tc_flags.push_back("-xc");
  } else {
    tc_flags.push_back("-xc++");
  }

  if (std()) {
    tc_flags.push_back(fmt::format("-std={}{}", c_lang() ? "c" : "c++", std()));
  }

  if (shared()) {
    tc_flags.push_back("-fPIC");
  }

  auto define_flag = [](auto& kv) {
    return fmt::format("-D{}={}", kv.first, kv.second);
  };

  tc_flags.append_range(defines() | views::transform(define_flag));

  auto undefine_flag = [](auto& k) { return fmt::format("-U{}", k); };

  tc_flags.append_range(undefines() | views::transform(undefine_flag));

  auto include_flag = [](auto& p) { return fmt::format("-I{}", p.string()); };
  tc_flags.append_range(includes() | views::transform(include_flag));

  tc_flags.append_range(c_lang() ? cc_flags() : cxx_flags());

  return tc_flags;
}

vector<path> toolchain::link_files() const {
  namespace views = std::views;
  namespace ranges = std::ranges;
  auto to_lib = [this](auto* l) { return l->out_file(); };
  vector<path> libraries =
      link_libraries() | views::transform(to_lib) | ranges::to<vector>();
  return libraries;
}
} // namespace buildxx
