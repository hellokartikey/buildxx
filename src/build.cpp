#include "buildxx.hpp"

// clang-format off
void buildxx::build(build_ctx& ctx, toolchain& tc) {
  tc.set_cxx_standard(cxx_std::cxx23);

  ctx.target<command>("echo2")
    .executable("echo")
    .option("Copy!")
    ;

  auto test = ctx.sub_directory("test");

  ctx.install(
    ctx.target<executable>("test_app")
      .sources(test, { "main.cpp", "foo.cpp" })
      .depends_on(
        ctx.target<command>("printenv")
          .executable("printenv")
          .environment("BUILDXX", "build++")
          .option("BUILDXX")
      )
  );
}
// clang-format on
