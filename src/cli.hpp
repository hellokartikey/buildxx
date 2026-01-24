#ifndef HK_BUILDXX_CLI_HPP
#define HK_BUILDXX_CLI_HPP

#include <memory>

#include <CLI/CLI.hpp>

#include "common.hpp"

int main(int, char**);

namespace bxx {
class cli : public std::enable_shared_from_this<cli> {
  struct private_tag {};

public:
  cli(private_tag);
  ~cli() = default;

  ptr<cli> get();

  bool is_verbose() const;
  const std::string& build_file() const;

private: // for friends
  friend int ::main(int, char**);

  static ptr<cli> create();

  void parse(int argc, char** argv);
  int exit(const CLI::ParseError& e);

private:
  CLI::App m_app;

  std::string m_build_file;
  bool m_verbose;
};
} // namespace bxx

#endif
