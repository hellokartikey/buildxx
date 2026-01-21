#ifndef HK_BUILDXX_CLI_HPP
#define HK_BUILDXX_CLI_HPP

#include <CLI/CLI.hpp>

namespace bxx {
class cli {
public:
  cli();
  ~cli() = default;

  inline const std::string& build_file() const { return m_build_file; }

  void parse(int argc, char** argv);
  int exit(const CLI::ParseError& e);

private:
  CLI::App m_app;

  std::string m_build_file;

  bool m_ok = true;
};
}

#endif
