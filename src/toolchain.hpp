#ifndef HK_BUILDXX_TOOLCHAIN_HPP
#define HK_BUILDXX_TOOLCHAIN_HPP

#include "common.hpp"
#include "step.hpp"

namespace buildxx {
class build_ctx;

struct object {
  fs::path object_file;
  fs::path source_file;
  step* build_step;
};

struct binary {
  fs::path binary_file;
  std::vector<object> object_files;
  step* link_step;
};

class toolchain {
public:
  toolchain() {}
  virtual ~toolchain() = default;

  virtual object build_cxx(build_ctx& ctx, fs::path source) = 0;
  virtual binary
  link_cxx(build_ctx& ctx, std::string name, std::vector<object> objects) = 0;

  template <class T> T& add_cxx_option(this T& self, std::string option) {
    self.m_cxx_opts.push_back(std::move(option));
    return self;
  }

  template <class T> T& add_cxx_options(this T& self, step::arguments options) {
    for (auto& option : options) {
      self.add_cxx_option(std::move(option));
    }
    return self;
  }

  step::arguments cxx_options(step::arguments options = {});

private:
  step::arguments m_cxx_opts;
};
} // namespace buildxx

#endif
