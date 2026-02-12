#include "executable.hpp"

#include "build_ctx.hpp"

namespace buildxx {
executable::executable(build_ctx& ctx, std::string name, fs::path entry)
    : target(ctx, name)
    , m_files({entry}) {}

auto executable::sources() const -> const source_files& { return m_files; }

executable& executable::add_source(fs::path file) {
  m_files.push_back(std::move(file));
  return *this;
}

executable& executable::add_source(fs::path prefix, source_files files) {
  for (auto& file : files) {
    add_source(prefix / file);
  }
  return *this;
}

void executable::create_steps(build_ctx& ctx, toolchain& tc) {
  std::vector<object> objects;

  for (const auto& file : m_files) {
    auto object = tc.build_cxx(ctx, file);
    objects.push_back(object);
  }

  auto binary = tc.link_cxx(ctx, name(), objects);
  final_step().depends_on(*binary.link_step);
}
} // namespace buildxx
