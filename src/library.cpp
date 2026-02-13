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
  std::vector<object> objects;
  for (const auto& file : m_files) {
    auto object = tc.build_cxx(ctx, file);
    objects.push_back(object);
  }

  std::vector<archive> archives;
  for (const auto& ar : m_link_libraries) {
    archives.push_back(ar->artifact().value());
  }

  switch (m_link) {
  case link::archive:
    m_archive = tc.ar_cxx(ctx, name(), objects, archives);
    break;
  case link::shared:
    throw std::runtime_error("shared library not yet implemented");
  default:
    throw std::runtime_error("invalid linkage for library");
  }
  final_step().depends_on(*m_archive.value().archive_step);
}
} // namespace buildxx
