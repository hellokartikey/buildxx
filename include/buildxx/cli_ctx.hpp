#ifndef BUILDXX_CLI_CTX_HPP
#define BUILDXX_CLI_CTX_HPP

#include "types.hpp"

namespace buildxx {
class cli_ctx;
cli_ctx& cli();

class cli_ctx {
private:
  cli_ctx() = default;
  ~cli_ctx() = default;

public:
  static int parse(int argc, char** argv);
  friend cli_ctx& cli();

  int argc() const;
  char** argv() const;

  bool verbose() const;
  const string& script() const;


private:
  int m_argc;
  char** m_argv;

  string m_script;
  bool m_verbose = false;
};
}

#endif
