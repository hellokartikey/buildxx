#include <buildxx/buildxx.hpp>

// clang-format off
void buildxx::buildxx() {
  auto test_dir = build().dir("test");

  auto foo_srcs = prefix(build().dir("test"), { "foo.cc", "bar.cc" });
  auto& foo = build()
    .add<library>("foo")
    .shared(true)
    .files(foo_srcs)
    ;

  auto& exe = build()
    .add<executable>("test")
    .file(test_dir / "main.cc")
    .link(foo)
    .include(test_dir)
    .install()
    ;
}
// clang-format on
