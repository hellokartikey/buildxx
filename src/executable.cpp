#include <buildxx/buildxx.hpp>

#include <ranges>

#include <spdlog/spdlog.h>

namespace buildxx {
executable::executable(build_ctx& ctx, const string& name)
    : target(ctx, name)
    , toolchain()
    , m_out_file(ctx.bin() / name) {}

executable& executable::out_file(const path& file) {
  m_out_file = file;
  return *this;
}

const path& executable::out_file() const { return m_out_file; }

executable& executable::build_steps() {
  namespace views = std::views;
  namespace ranges = std::ranges;

  auto to_object = [this](auto p) {
    return this->ctx().tmp() / p.relative_path().concat(".o");
  };

  vector<path> objects =
      files() | views::transform(to_object) | ranges::to<vector>();

  auto tc_flags = build_flags();

  for (auto [in, out] : views::zip(files(), objects)) {
    auto& object_step =
        ctx()
            .step()
            .bin(c_lang() ? cc() : cxx())
            .flags(tc_flags)
            .flag("-c")
            .flag("-o")
            .out_file(out)
            .in_file(in)
            .message(fmt::format("Building binary object {}", out.string()))
            .depends_on(first_step());

    final_step().depends_on(object_step);
  }

  final_step()
      .bin(c_lang() ? cc() : cxx())
      .flags(ld_flags())
      .flag("-o")
      .out_file(out_file())
      .in_files(objects)
      .in_files(link_files())
      .message(fmt::format("Linking executable {}", out_file().string()));

  return *this;
}

shell& executable::run_step() {
  return ctx()
      .step()
      .bin(out_file())
      .depends_on(final_step())
      .message(fmt::format("Running executable {}", name()));
}
} // namespace buildxx
