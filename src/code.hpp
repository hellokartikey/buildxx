#ifndef HK_BUILDXX_CODE_HPP
#define HK_BUILDXX_CODE_HPP

#include <vector>

#include "common.hpp"

namespace buildxx {
class library;

class code_mixin {
public:
  using source_files = std::vector<fs::path>;

  const source_files& get_sources() const { return m_files; }

  auto& source(this auto& self, fs::path file) {
    self.m_files.push_back(file);
    return self;
  }

  auto& sources(this auto& self, source_files files) {
    for (auto& file : files) {
      self.source(file);
    }
    return self;
  }

  auto& sources(this auto& self, fs::path prefix, source_files files) {
    for (auto& file : files) {
      self.source(prefix / file);
    }
    return self;
  }

  auto& link(this auto& self, library& lib) {
    self.m_link_libraries.push_back(&lib);
    self.depends_on(lib);
    return self;
  }

protected:
  source_files m_files{};
  std::vector<library*> m_link_libraries;
};
} // namespace buildxx

#endif
