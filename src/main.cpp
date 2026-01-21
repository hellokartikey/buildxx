#include <boost/process.hpp>

#include "cli.hpp"
#include "unix_toolchain.hpp"

int main(int argc, char** argv) {
  using namespace bxx;

  // 1. parse cli args
  cli app;
  CLI11_PARSE(app, argc, argv);

  // 2. detect tool chain
  auto gnu = tc::unix_toolchain{};

  // 3. compile
  asio::io_context ctx;
  proc::process proc(ctx, gnu.cxx(), { app.build_file() });
  proc.wait();

  return 0;
}
