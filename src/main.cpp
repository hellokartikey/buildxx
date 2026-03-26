#include <spdlog/spdlog.h>

#include "build_ctx.hpp"
#include "shell.hpp"

using namespace buildxx;
using namespace std::literals;

co::main co_main(int argc, char** argv) {
  spdlog::set_pattern("[%^%l%$] %v");

  build_ctx ctx;

  auto& sleep = ctx.step().bin("sleep").flag("5").message("first echo");
  auto& sleep_msg = ctx.step().bin("echo").flag("sleep completed").depends_on(sleep);

  auto& dep = ctx.step().bin("echo").flag("dependency");

  auto& echo = ctx.step().bin("echo").flag("Hello").depends_on(sleep_msg).depends_on(dep);

  co_await echo.exec();

  co_return 0;
}
