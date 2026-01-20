#include <print>

#include <boost/process.hpp>
#include <CLI/CLI.hpp>

namespace proc = boost::process;
namespace env = proc::environment;

int main(int argc, char** argv) {
  CLI::App app{"buildxx"};
  argv = app.ensure_utf8(argv);

  std::string file;
  app.add_option("file", file, "File to compile")->required();
  CLI11_PARSE(app, argc, argv);

  auto cxx = env::find_executable("g++");
  std::println("Found compiler {}", cxx.string());

  boost::asio::io_context ctx;
  proc::process proc(ctx, cxx, { file });
  proc.wait();

  return 0;
}
