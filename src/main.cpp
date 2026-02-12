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

  try {
    // 1. parse cli args
    auto ctx = buildxx::build_ctx{};

    // 2. create build graph
    buildxx::build(ctx);

    // 3. parse cli options
    CLI11_PARSE(ctx.cli(), argc, argv);

    // 4.1 list all targets
    if (ctx.cli().list_targets()) {
      ctx.list_targets();
      return 0;
    }

    // 4.2 build default install step
    ctx.build_install_steps();

  } catch (std::runtime_error& e) {
    spdlog::critical("buildxx error: {}", e.what());
    return 1;
  }

  return 0;
}

// clang-format off
void buildxx::build(build_ctx& ctx) {
  auto test = ctx.sub_directory("test");

  auto& echo =
     command::add(ctx, "echo_hello", "echo")
    .add_option("Hello from build++");

  auto& echo_2 =
     command::add(ctx, "echo_hello_2", "echo")
    .add_option("Copy!");

  auto& test_app =
     executable::add(ctx, "test_app", test / "main.cpp")
    .add_source(test, { "foo.cpp" })
    .depends_on(echo);
    ;

  ctx.install(test_app);
}
// clang-format on
