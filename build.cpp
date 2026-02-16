#include "src/buildxx.hpp"

// clang-format off
void buildxx::build(build_ctx& ctx, toolchain& tc) {
  tc.cxx_standard(std_cxx::cxx23);

  ctx.target<command>("echo2")
    .executable("echo")
    .option("Copy!")
    ;

  auto test = ctx.sub_directory("test");

  ctx.install(
    ctx.target<executable>("test_app")
      .sources(test, { "main.cpp" })
      .depends_on(
        ctx.target<command>("printenv")
          .executable("printenv")
          .environment("BUILDXX", "build++")
          .option("BUILDXX")
      )
      .link(
        ctx.target<library>("foo")
          .linkage(link::shared)
          .source(test / "foo.cpp")
      )
  );
}
// clang-format on
