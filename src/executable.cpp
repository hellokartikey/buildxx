#include "executable.hpp"

#include <ranges>

#include <spdlog/spdlog.h>

#include "build_ctx.hpp"

namespace buildxx {
executable::executable(build_ctx& ctx, const string& name)
    : target(ctx, name)
    , m_out_file(ctx.bin() / name)
    , m_first_step(&ctx.step())
    , m_link_step(&ctx.step()) {}

const path& executable::out_file() const { return m_out_file; }

shell& executable::first_step() { return *m_first_step; }

shell& executable::final_step() { return *m_link_step; }

executable& executable::build_steps() {
  namespace views = std::views;
  namespace ranges = std::ranges;

  auto to_object = [this](auto p) {
    return this->ctx().tmp() / fs::relative(p.concat(".o"));
  };

  auto tc_flags = build_flags();

  vector<path> objects =
      files() | views::transform(to_object) | ranges::to<vector<path>>();

  for (auto [in, out] : views::zip(files(), objects)) {
    auto& object_step = ctx()
                            .step()
                            .bin(c_lang() ? cc() : cxx())
                            .flag("-c")
                            .flags(tc_flags)
                            .flag("-o")
                            .out_file(out)
                            .in_file(in)
                            .message(fmt::format("Building binary object {}",
                                                 fs::relative(out).string()))
                            .depends_on(first_step());

    final_step().depends_on(object_step);
  }

  final_step()
      .bin(c_lang() ? cc() : cxx())
      .flags(ld_flags())
      .flag("-o")
      .out_file(out_file())
      .in_files(objects)
      .message(fmt::format("Linking executable {}",
                           fs::relative(out_file()).string()));

  return *this;
}
} // namespace buildxx
