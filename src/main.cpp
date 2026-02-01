#include <boost/process.hpp>

#include <spdlog/spdlog.h>

#include "cli.hpp"
#include "ctx.hpp"

namespace bxx {
void build(ptr<ctx> b);
}

int main(int argc, char** argv) {
  // 0. setup environment
  spdlog::set_pattern("[%^%l%$] %v");

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
void bxx::build(ptr<ctx> b) {
  auto test = b->sub_dir("test");

  auto echo = b
    ->add_cmd("echo")
    ->add_opt("Hello from build++")
    ;

  auto app = b
    ->add_exe("test_app", test / "main.cpp")
    ->add_src(test, { "foo.cpp" })
    ->depends_on(echo)
    ->install()
    ;
}
// clang-format on
