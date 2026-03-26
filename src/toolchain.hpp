#ifndef BUILDXX_TOOLCHAIN_HPP
#define BUILDXX_TOOLCHAIN_HPP

#include "types.hpp"

#include <fmt/format.h>

namespace buildxx {
class library;

class toolchain {
public:
  toolchain();
  ~toolchain() = default;

  int std() const;

  auto& std(this auto& self, int version) {
    self.m_std = version;
    return self;
  }

  bool c_lang() const;

  auto& c_lang(this auto& self, bool value) {
    self.m_c = value;
    return self;
  }

  bool shared() const;

  auto& shared(this auto& self, bool value) {
    self.m_shared = value;
    return self;
  }

  const path& cxx() const;

  auto& cxx(this auto& self, const path& bin) {
    self.m_cxx = env::find_executable(bin);
    return self;
  }

  const path& cc() const;

  auto& cc(this auto& self, const path& bin) {
    self.m_cc = env::find_executable(bin);
    return self;
  }

  const path& ld() const;

  auto& ld(this auto& self, const path& bin) {
    self.m_ld = env::find_executable(bin);
    return self;
  }

  const path& ar() const;

  auto& ar(this auto& self, const path& bin) {
    self.m_ar = env::find_executable(bin);
    return self;
  }

  const vector<path>& includes() const;

  auto& include(this auto& self, const path& dir) {
    self.m_includes.push_back(dir);
    return self;
  }

  const map<string, string>& defines() const;

  auto& define(this auto& self, const string& name, const string& value) {
    self.m_defines[name] = value;
    return self;
  }

  auto& define(this auto& self, const string& name) {
    using namespace std::literals;
    return self.define(name, ""s);
  }

  const vector<string>& undefines() const;

  auto& undefine(this auto& self, const string& name) {
    self.m_undefines.push_back(name);
    return self;
  }

  const vector<string>& cxx_flags() const;

  auto& cxx_flag(this auto& self, const string& flag) {
    self.m_cxx_flags.push_back(flag);
    return self;
  }

  auto& cxx_flags(this auto& self, const vector<string>& flags) {
    self.m_cxx_flags.append_range(flags);
    return self;
  }

  const vector<string>& cc_flags() const;

  auto& cc_flag(this auto& self, const string& flag) {
    self.m_cc_flags.push_back(flag);
    return self;
  }

  auto& cc_flags(this auto& self, const vector<string>& flags) {
    self.m_cc_flags.append_range(flags);
    return self;
  }

  const vector<string>& ld_flags() const;

  auto& ld_flag(this auto& self, const string& flag) {
    self.m_ld_flags.push_back(flag);
    return self;
  }

  auto& ld_flags(this auto& self, const vector<string>& flags) {
    self.m_ld_flags.append_range(flags);
    return self;
  }

  const vector<string>& ar_flags() const;

  auto& ar_flag(this auto& self, const string& flag) {
    self.m_ar_flags.push_back(flag);
    return self;
  }

  auto& ar_flags(this auto& self, const vector<string>& flags) {
    self.m_ar_flags.append_range(flags);
    return self;
  }

  vector<library*> link_libraries() const;

  template <typename T, typename U>
  auto& link(this T& self, U& lib)
    requires(std::same_as<U, library>)
  {
    self.first_step().depends_on(lib.final_step());
    self.m_link.push_back(&lib);
    return self;
  }

  vector<string> build_flags() const;
  vector<path> link_files() const;

  auto& merge(this auto& self, const toolchain& other);

private:
  int m_std = 0;
  bool m_c = false;
  bool m_shared = false;

  path m_cxx;
  path m_cc;
  path m_ld;
  path m_ar;

  vector<string> m_cxx_flags;
  vector<string> m_cc_flags;
  vector<string> m_ld_flags;
  vector<string> m_ar_flags;

  vector<path> m_includes;
  map<string, string> m_defines;
  vector<string> m_undefines;

  vector<library*> m_link;
};
} // namespace buildxx

#endif
