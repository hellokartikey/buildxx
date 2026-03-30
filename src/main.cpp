#include <buildxx/buildxx.hpp>

#include <boost/cobalt/main.hpp>
#include <spdlog/spdlog.h>
#include <CLI/CLI.hpp>

using namespace buildxx;
namespace co = boost::cobalt;

co::main co_main(int argc, char** argv) {
  spdlog::set_pattern("[%^%l%$] %v");

  CLI::App app{"Modern C++ built tool."};

  std::string build_cc;
  app.add_option("script", build_cc, "The build script")
      ->default_val("build.cpp");

  bool verbose;
  app.add_flag("-v,--verbose", verbose, "Verbose output")->default_val(false);

  argv = app.ensure_utf8(argv);

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    co_return app.exit(e);
  }

  try {
    build_ctx ctx(argc, argv, build_cc);
    build(ctx);
    co_await ctx.build_step().exec(verbose);
  } catch (error& e) {
    spdlog::error(e.what());
  } catch (std::exception& e) {
    spdlog::error(fmt::format("unknown: {}", e.what()));
  }

  co_return 0;
}
