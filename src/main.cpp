#include <boost/process.hpp>

#include <spdlog/spdlog.h>

#include "cli.hpp"
#include "build_ctx.hpp"
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
