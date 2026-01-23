#include <boost/process.hpp>

#include "cli.hpp"
#include "ctx.hpp"

int main(int argc, char** argv) {
  using namespace bxx;

  // 1. parse cli args
  cli app;
  CLI11_PARSE(app, argc, argv);

  // 2. detect build context
  auto ctx = bxx::ctx{};

  // 3. create steps
  auto test = ctx.sub_directory("test");

  auto& echo = ctx
    .add_step(env::find_executable("echo"))
    .add_option("Hello from buildxx")
    ;

  auto& compile = ctx
    .add_step(ctx.toolchain().cxx())
    .add_path_option(test / app.build_file())
    .add_option("-otest_app")
    .depends_on(echo)
    .install()
    ;

  // 4. compile
  ctx.build();

  return 0;
}
