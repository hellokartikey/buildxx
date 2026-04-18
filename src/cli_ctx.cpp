#include "buildxx/cli_ctx.hpp"

#include <CLI/CLI.hpp>

namespace buildxx {
cli_ctx& cli() {
  static cli_ctx cli;
  return cli;
}

int cli_ctx::parse(int argc, char** argv) {
  auto& ctx = cli();

  ctx.m_argc = argc;
  ctx.m_argv = argv;

  CLI::App app{"Modern C++ built tool."};

  app.add_option("script", ctx.m_script, "The build script")
      ->default_val("build.cpp");

  app.add_flag("-v,--verbose", ctx.m_verbose, "Verbose output")
      ->default_val(false);

  argv = app.ensure_utf8(argv);

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  return 0;
}

int cli_ctx::argc() const { return m_argc; }

char** cli_ctx::argv() const { return m_argv; }

bool cli_ctx::verbose() const { return m_verbose; }

const string& cli_ctx::script() const { return m_script; }
}
