#include "buildxx/buildxx.hpp"

#include <boost/cobalt/main.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

using namespace buildxx;
namespace co = boost::cobalt;

co::main co_main(int argc, char** argv) {
  spdlog::set_pattern("[%^%l%$] %v");

  if (auto rc = cli_ctx::parse(argc, argv); rc) {
    co_return rc;
  }

  try {
    buildxx::buildxx();
    build().build_step().exec(cli().verbose());
  } catch (error& e) {
    spdlog::error(e.what());
    co_return 1;
  } catch (std::exception& e) {
    spdlog::error(fmt::format("unknown: {}", e.what()));
    co_return 2;
  }

  co_return 0;
}
