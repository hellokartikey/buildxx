#include <boost/process.hpp>

#include <spdlog/spdlog.h>

#include "build_ctx.hpp"
#include "cli.hpp"
#include "command.hpp"
#include "executable.hpp"
#include "unix_toolchain.hpp"

namespace buildxx {
void build(build_ctx&, toolchain&);
}

int main(int argc, char** argv) {
  // 0. setup environment
  spdlog::set_pattern("[%^%l%$] %v");

  try {

    // 1. initialize systems
    buildxx::cli cli;
    buildxx::build_ctx ctx;
    buildxx::unix_toolchain tc;

    // 2. create build graph
    buildxx::build(ctx, tc);

    // 3. parse cli options
    CLI11_PARSE(cli, argc, argv);

    // 4.1 list all targets
    if (cli.list_targets()) {
      return ctx.list_targets();
    }

    // 4.2 build default install step
    return ctx.build_install_steps(tc, cli.target(), cli.is_verbose());

  } catch (std::runtime_error& e) {
    spdlog::critical("buildxx error: {}", e.what());
    return 1;
  }

  return 1;
}

// clang-format off
void buildxx::build(build_ctx& ctx) {
  auto test = ctx.sub_directory("test");

  auto& echo =
     command::add(ctx, "echo_hello", "echo")
    .add_option("Hello from build++")
    ;

  auto& echo_2 =
     command::add(ctx, "test", "echo")
    .add_option("Copy!")
    ;

  auto& test_app =
     executable::add(ctx, "test_app", test / "main.cpp")
    .add_source(test, { "foo.cpp" })
    .depends_on(echo);
    ;

  ctx.install(test_app);
}
// clang-format on
