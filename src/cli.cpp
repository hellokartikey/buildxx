#include "cli.hpp"

namespace bxx {
cli::cli(private_tag) {
  m_app.add_option("file", m_build_file, "Build description")->required();
  m_app.add_flag("-v", m_verbose, "Verbose output")->default_val(false);
}

ptr<cli> cli::create() { return std::make_shared<cli>(private_tag{}); }

ptr<cli> cli::get() { return shared_from_this(); }

bool cli::is_verbose() const { return m_verbose; }

const std::string& cli::build_file() const { return m_build_file; }

void cli::parse(int argc, char** argv) { m_app.parse(argc, argv); }

int cli::exit(const CLI::ParseError& e) { return m_app.exit(e); }
} // namespace bxx
