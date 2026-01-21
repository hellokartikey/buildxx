#include "cli.hpp"

namespace bxx::cli {
cli::cli() {
  m_app.add_option("file", m_build_file, "Build description")->required();
}

void cli::parse(int argc, char** argv) {
  m_app.parse(argc, argv);
}

int cli::exit(const CLI::ParseError& e) {
  return m_app.exit(e);
}
}
