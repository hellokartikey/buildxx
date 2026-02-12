#ifndef HK_BUILDXX_CLI_HPP
#define HK_BUILDXX_CLI_HPP

#include <CLI/CLI.hpp>

namespace buildxx {
class cli {
public:
  static constexpr auto* INSTALL = "install";

  cli();
  ~cli() = default;

  bool is_verbose() const;
  const std::string& build_file() const;

  bool list_targets() const;
  const std::string& target() const;

  void parse(int argc, char** argv);
  int exit(const CLI::ParseError& e);

private:
  CLI::App m_app{};

  std::string m_build_file{};
  std::string m_target{};
  bool m_verbose{};
  bool m_targets{};
};
} // namespace buildxx

#endif
