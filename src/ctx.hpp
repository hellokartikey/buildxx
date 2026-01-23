#ifndef HK_BUILDXX_CTX_HPP
#define HK_BUILDXX_CTX_HPP

#include <memory>
#include <vector>

#include "toolchain.hpp"
#include "step.hpp"

namespace bxx {
class ctx {
public:
  ctx();
  ~ctx() = default;

  inline toolchain& toolchain() { return *m_tc; }
  inline asio::io_context& executor() { return m_io; }

  fs::path sub_directory(std::string dir) const;

  step& add_step(fs::path exe, step::arguments args = {}, step::environment env = {});

  ctx& build();

private:
  friend step;
  void install_step(step& step);

private:
  std::unique_ptr<bxx::toolchain> m_tc;
  asio::io_context m_io;

  std::vector<std::unique_ptr<step>> m_steps;
  std::vector<step*> m_install;
};
}

#endif
