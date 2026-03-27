#include <buildxx/buildxx.hpp>

#include <ranges>

namespace buildxx {
library::library(build_ctx& ctx, const string& name)
    : target(ctx, name)
    , toolchain()
    , m_out_file(ctx.lib() / fmt::format("lib{}.a", name)) {}

library& library::shared(bool value) {
  toolchain::shared(value);

  if (toolchain::shared()) {
    m_out_file = ctx().lib() / fmt::format("lib{}.so", name());
  } else {
    m_out_file = ctx().lib() / fmt::format("lib{}.a", name());
  }

  return *this;
}

const path& library::out_file() const { return m_out_file; }

library& library::build_steps() {
  namespace views = std::views;
  namespace ranges = std::ranges;

  auto to_object = [this](auto p) {
    return this->ctx().tmp() / p.relative_path().concat(".o");
  };

  auto tc_flags = build_flags();

  vector<path> objects =
      files() | views::transform(to_object) | ranges::to<vector<path>>();

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

  if (toolchain::shared()) {
    final_step()
        .bin(c_lang() ? cc() : cxx())
        .flag("-shared")
        .flags(ld_flags())
        .flag("-o")
        .out_file(out_file())
        .in_files(objects)
        .in_files(link_files())
        .message(fmt::format("Linking shared library {}", out_file().string()));
  } else {
    final_step()
        .bin(ar())
        .flag("rcs")
        .flags(ar_flags())
        .flag("-o")
        .out_file(out_file())
        .in_files(objects)
        .in_files(link_files())
        .message(fmt::format("Linking static library {}", out_file().string()));
  }

  return *this;
}
} // namespace buildxx
