#include "src/buildxx/buildxx.hpp"

// clang-format off
void buildxx::build(build_ctx& ctx) {
  auto test_dir = ctx.dir("test");

  auto& foo = ctx.add<library>("foo")
    .file(test_dir / "foo.cc");

  auto& exe = ctx.add<executable>("test")
    .file(test_dir / "main.cc")
    .link(foo)
    .include(test_dir)
    .build();
}
// clang-format on
