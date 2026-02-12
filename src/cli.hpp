#ifndef HK_BUILDXX_CLI_HPP
#define HK_BUILDXX_CLI_HPP

#include <CLI/CLI.hpp>

namespace buildxx {
class cli {
public:
  cli();
  ~cli() = default;

  bool is_verbose() const;
  bool list_targets() const;
  const std::string& build_file() const;

  void parse(int argc, char** argv);
  int exit(const CLI::ParseError& e);

private:
  CLI::App m_app{};

  std::string m_build_file{};
  bool m_verbose{};
  bool m_targets{};
};
} // namespace buildxx

#endif
