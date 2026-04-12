#include <buildxx/buildxx.hpp>

// clang-format off
void buildxx::build(build_ctx& ctx) {
  auto test_dir = ctx.dir("test");

  auto foo_srcs = prefix(ctx.dir("test"), { "foo.cc", "bar.cc" });
  auto& foo = ctx.add<library>("foo")
    .shared(true)
    .files(foo_srcs);

  auto& exe = ctx.add<executable>("test")
    .file(test_dir / "main.cc")
    .link(foo)
    .include(test_dir)
    .build();
}
// clang-format on
