#include <spdlog/spdlog.h>

#include "build.hpp"
#include "build_ctx.hpp"

using namespace buildxx;

co::main co_main(int argc, char** argv) {
  spdlog::set_pattern("[%^%l%$] %v");

  build_ctx ctx;

  build(ctx);

  try {
    co_await ctx.build_step().exec();
  } catch (error& e) {
    spdlog::error(e.what());
  } catch (std::exception& e) {
    spdlog::error(fmt::format("unknown: {}", e.what()));
  }

  co_return 0;
}
