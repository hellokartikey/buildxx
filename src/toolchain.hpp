#ifndef HK_BUILDXX_TOOLCHAIN_HPP
#define HK_BUILDXX_TOOLCHAIN_HPP

#include "common.hpp"
#include "step.hpp"

namespace buildxx {
class build_ctx;

enum class link { archive, shared };
enum class cxx_std { cxx98, cxx11, cxx14, cxx17, cxx20, cxx23, cxx26 };

struct object {
  fs::path object_file;
  fs::path source_file;
  step* build_step;
};

using objects = std::vector<object>;

struct binary {
  fs::path binary_file;
  step* link_step;
};

using binaries = std::vector<binary>;

struct archive {
  fs::path archive_file;
  step* archive_step;
  link linkage;
};

using archives = std::vector<archive>;

class toolchain {
public:
  static constexpr std::format_string<const std::string&> CXX_OBJ =
      "Building C++ object {}";
  static constexpr std::format_string<const std::string&> CXX_LINK =
      "Linking C++ executable {}";
  static constexpr std::format_string<const std::string&> CXX_AR =
      "Linking C++ archive {}";

  toolchain() {}
  virtual ~toolchain() = default;

  virtual object build_cxx(build_ctx& ctx, fs::path source) = 0;

  virtual binary link_cxx(build_ctx& ctx,
                          std::string name,
                          objects objects,
                          archives archives) = 0;

  virtual archive ar_cxx(build_ctx& ctx,
                         std::string name,
                         objects objects,
                         archives archives) = 0;

  virtual toolchain& set_cxx_standard(cxx_std std) = 0;

public:
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

  template <class T> T& add_ar_option(this T& self, std::string option) {
    self.m_ar_opts.push_back(std::move(option));
    return self;
  }

  template <class T> T& add_ar_options(this T& self, step::arguments options) {
    for (auto& option : options) {
      self.add_ar_option(std::move(option));
    }
    return self;
  }

  step::arguments cxx_options(step::arguments options = {});
  step::arguments ar_options(step::arguments options = {});

private:
  step::arguments m_cxx_opts;
  step::arguments m_ar_opts;
};
} // namespace buildxx

#endif
