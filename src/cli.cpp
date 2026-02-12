#include "cli.hpp"

namespace buildxx {
cli::cli() {
  m_app.add_option("file", m_build_file, "Build description")->required();
  m_app.add_flag("-v", m_verbose, "Verbose output")->default_val(false);
  m_app.add_flag("--targets", m_targets, "Print targets")->default_val(false);
}

bool cli::is_verbose() const { return m_verbose; }

bool cli::list_targets() const { return m_targets; }

const std::string& cli::build_file() const { return m_build_file; }

void cli::parse(int argc, char** argv) { m_app.parse(argc, argv); }

int cli::exit(const CLI::ParseError& e) { return m_app.exit(e); }
} // namespace buildxx
