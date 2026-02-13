#include "library.hpp"

#include "toolchain.hpp"

namespace buildxx {
library::library(build_ctx& ctx, std::string name)
    : target(ctx, name) {}

link library::get_linkage() const { return m_link; }

library& library::linkage(enum link type) {
  m_link = type;
  return *this;
}

const std::optional<archive>& library::artifact() const { return m_archive; }

void library::create_steps(build_ctx& ctx, toolchain& tc) {
  // 1. get archives of dependencies
  std::vector<archive> archives;
  for (const auto& ar : m_link_libraries) {
    archives.push_back(ar->artifact().value());
  }

  // 2. build own objects
  std::vector<object> objects;

  switch (m_link) {
  case link::archive:
    objects = tc.build_cxx(ctx, m_files);
    m_archive = tc.ar_cxx(ctx, name(), objects, archives);
    break;
  case link::shared:
    objects = tc.build_cxx_shared(ctx, m_files);
    m_archive = tc.link_cxx_shared(ctx, name(), objects, archives);
    break;
  default:
    throw std::runtime_error("invalid linkage for library");
  }

  final_step().depends_on(*m_archive.value().archive_step);
}
} // namespace buildxx
