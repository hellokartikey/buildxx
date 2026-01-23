#ifndef HK_BUILDXX_CLI_HPP
#define HK_BUILDXX_CLI_HPP

#include <memory>

#include <CLI/CLI.hpp>

#include "ctx.hpp"

namespace bxx {
class cli {
public:
  cli();
  ~cli() = default;

  inline const std::string& build_file() const { return m_build_file; }

  inline std::shared_ptr<ctx> build_ctx() { return m_ctx; }

  inline void build() { m_ctx->build(); }

  void parse(int argc, char** argv);
  int exit(const CLI::ParseError& e);

private:
  CLI::App m_app;

  std::string m_build_file;

  std::shared_ptr<ctx> m_ctx;

  bool m_ok = true;
};
}

#endif
