#include <boost/process.hpp>

#include "cli.hpp"
#include "ctx.hpp"

namespace bxx {
void build(std::shared_ptr<ctx> ctx);
}

int main(int argc, char** argv) {
  // 1. parse cli args
  bxx::cli app;
  CLI11_PARSE(app, argc, argv);

  // 2. call build description
  bxx::build(app.build_ctx());

  // 3. compile
  app.build();

  return 0;
}

// clang-format off
void bxx::build(std::shared_ptr<ctx> b) {
  auto test = b->sub_directory("test");

  auto echo = b
    ->add_command("echo")
    ->add_option("Hello from build++")
    ->install();

  // auto compile = ctx
  //   .add_step(ctx.toolchain().cxx())
  //   .add_path_option(test / app.build_file())
  //   .add_option("-otest_app")
  //   .depends_on(echo)
  //   .install()
  //   ;
}
// clang-format on
