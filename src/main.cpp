#include <boost/process.hpp>

#include <spdlog/spdlog.h>

#include <dylib.hpp>

#include "build_ctx.hpp"
#include "cli.hpp"
#include "unix_toolchain.hpp"

int main(int argc, char** argv) {
  // 0. setup environment
  using namespace buildxx;
  spdlog::set_pattern("[%^%l%$] %v");

  try {
    // 1. parse cli options
    cli cli;
    CLI11_PARSE(cli, argc, argv);

    // 2. initialize systems
    build_ctx ctx(cli.build_file());
    unix_toolchain tc;

    // 3. compile build script
    tc.cxx_standard(cxx_std::cxx23);
    auto script = ctx.build_script(tc, cli.is_verbose());
    tc.reset();

    // 4. load build lib
    dylib::library lib(script.string());

    // 5. create build graph
    auto build =
        lib.get_function<void(build_ctx&, toolchain&)>("buildxx::build");
    build(ctx, tc);

    // 6.1 list all targets
    if (cli.list_targets()) {
      return ctx.list_targets();
    }

    // 6.2 build default install step
    return ctx.build_target(tc, cli.target(), cli.is_verbose());

  } catch (const std::runtime_error& e) {
    spdlog::critical("buildxx error: {}", e.what());
    return 1;
  }

  return 1;
}
