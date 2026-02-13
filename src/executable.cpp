#include "executable.hpp"

#include "build_ctx.hpp"
#include "library.hpp"

namespace buildxx {
executable::executable(build_ctx& ctx, std::string name)
    : target(ctx, name) {}

const std::optional<binary>& executable::artifact() const { return m_binary; }

void executable::create_steps(build_ctx& ctx, toolchain& tc) {
  std::vector<object> objects;
  for (const auto& file : m_files) {
    auto object = tc.build_cxx(ctx, file);
    objects.push_back(object);
  }

  std::vector<archive> archives;
  for (const auto& ar : m_link_libraries) {
    auto archive = ar->artifact();
    archives.push_back(archive.value());
  }

  m_binary = tc.link_cxx(ctx, name(), objects, archives);
  final_step().depends_on(*m_binary.value().link_step);
}
} // namespace buildxx
