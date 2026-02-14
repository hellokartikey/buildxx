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
  using fmt = std::format_string<const std::string&>;
  static constexpr fmt CXX_OBJ = "Building C++ object {}";
  static constexpr fmt CXX_LINK = "Linking C++ executable {}";
  static constexpr fmt CXX_AR = "Linking C++ archive {}";
  static constexpr fmt CXX_SO = "Linking C++ library {}";

  toolchain() {}
  virtual ~toolchain() = default;

  virtual object build_cxx(build_ctx& ctx, fs::path source) = 0;
  objects build_cxx(build_ctx& ctx, std::vector<fs::path> sources);

  virtual binary link_cxx(build_ctx& ctx,
                          std::string name,
                          objects objects,
                          archives archives) = 0;

  virtual archive link_cxx_shared(build_ctx& ctx,
                                  std::string name,
                                  objects objects,
                                  archives archives) = 0;

  virtual archive ar_cxx(build_ctx& ctx,
                         std::string name,
                         objects objects,
                         archives archives) = 0;

  virtual toolchain& cxx_standard(cxx_std std) = 0;

  virtual toolchain& include(fs::path path) = 0;

public:
  template <class T> T& cxx_flag(this T& self, std::string option) {
    self.m_cxx_flags.push_back(option);
    return self;
  }

  template <class T> T& cxx_flags(this T& self, step::arguments options) {
    for (auto& option : options) {
      self.cxx_flag(option);
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

  template <class T> T& reset(this T& self) {
    self.m_cxx_flags.clear();
    self.m_cxx_define.clear();
    self.m_cxx_include.clear();
    self.m_ar_opts.clear();

    return self;
  }

  step::arguments cxx_options(step::arguments flags = {});
  step::arguments ar_options(step::arguments flags = {});

private:
  step::arguments m_cxx_flags;
  step::arguments m_cxx_define;
  step::arguments m_cxx_include;

  step::arguments m_ar_opts;
};
} // namespace buildxx

#endif
