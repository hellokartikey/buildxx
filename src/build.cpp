#include "build.hpp"

#include "executable.hpp"

void buildxx::build(build_ctx& ctx) {
  auto& echo = ctx.step().bin("echo").flag("Hello, World!");

  auto& test = ctx.add<executable>("test")
                   .std(23)
                   .file(ctx.dir("test") / "main.cc")
                   .define("TEST")
                   .depends_on(echo)
                   .build();
}
