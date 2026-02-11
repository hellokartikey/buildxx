#include <boost/process.hpp>

#include <spdlog/spdlog.h>

#include "build_ctx.hpp"
#include "command.hpp"
#include "executable.hpp"

namespace buildxx {
void build(build_ctx&);
}

int main(int argc, char** argv) {
  // 0. setup environment
  spdlog::set_pattern("[%^%l%$] %v");

  // 1. parse cli args
  auto ctx = buildxx::build_ctx{};
  CLI11_PARSE(ctx.cli(), argc, argv);

  // 2. create build graph
  buildxx::build(ctx);

  // 3. compile
  try {
    ctx.build_install_steps();
  } catch (std::runtime_error& e) {
    spdlog::critical("error: {}", e.what());
    return 1;
  }

  return 0;
}

// clang-format off
void buildxx::build(build_ctx& ctx) {
  auto test = ctx.sub_directory("test");

  ctx.toolchain().set_std(cxx::cxx20);

  auto echo =
     command(ctx, "echo")
    .add_option("Hello from build++")
    ;

  auto test_app =
     executable(ctx, "test_app", test / "main.cpp")
    .add_source(test, { "foo.cpp" })
    .depends_on(echo);
    ;

  ctx.install(test_app);
}
// clang-format on
