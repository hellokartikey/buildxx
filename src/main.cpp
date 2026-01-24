#include <boost/process.hpp>

#include "cli.hpp"
#include "ctx.hpp"

namespace bxx {
void build(std::shared_ptr<ctx> ctx);
}

int main(int argc, char** argv) {
  // 1. parse cli args
  auto ctx = bxx::ctx::create(bxx::cli::create());
  CLI11_PARSE(*(ctx->cli()), argc, argv);

  // 2. call build description
  bxx::build(ctx);

  // 3. compile
  ctx->build();

  return 0;
}

// clang-format off
void bxx::build(std::shared_ptr<ctx> b) {
  auto test = b->sub_directory("test");

  auto echo = b
    ->add_command("echo")
    ->add_option("Hello from build++")
    ;

  auto err = b
    ->add_command("false");

  auto app = b
    ->add_executable("test_app", test / "main.cpp")
    ->depends_on(echo)
    ->install()
    ;
}
// clang-format on
