#include "build.hpp"

#include "executable.hpp"
#include "library.hpp"

void buildxx::build(build_ctx& ctx) {
  auto& echo = ctx.step().bin("echo").flag("Hello, World!");

  auto test_dir = ctx.dir("test");

  auto& foo = ctx.add<library>("foo")
                  .file(test_dir / "foo.cc")
                  .shared(true)
                  .c_lang(true);

  auto& test = ctx.add<executable>("test")
                   .std(23)
                   .c_lang(true)
                   .file(test_dir / "main.cc")
                   .define("TEST")
                   .include(test_dir)
                   .link(foo)
                   .depends_on(echo)
                   .build();
}
