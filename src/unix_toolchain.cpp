#include "unix_toolchain.hpp"

#include "build_ctx.hpp"

namespace buildxx {
unix_toolchain::unix_toolchain(std::string prefix)
    : toolchain() {
  m_cc = env::find_executable(prefix + "cc");
  m_cxx = env::find_executable(prefix + "c++");
  m_ar = env::find_executable(prefix + "ar");
}

object unix_toolchain::build_cxx(build_ctx& ctx, fs::path src) {
  auto src_file = ctx.directory() / src;
  auto obj_file = ctx.tmp() / src;
  obj_file += ".o";

  // 1. create object folder if not exists
  if (!fs::exists(obj_file.parent_path())) {
    fs::create_directory(obj_file.parent_path());
  }

  // 2. compile object step
  auto& build_step =
      ctx.add_step(m_cxx, cxx_options({"-x", "c++"}), {})
          .option("-c")
          .option(src.string())
          .options({"-o", obj_file.string()})
          .message(std::format(CXX_OBJ, obj_file.relative_path().string()));

  return {.object_file = obj_file,
          .source_file = src_file,
          .build_step = &build_step};
}

binary unix_toolchain::link_cxx(build_ctx& ctx,
                                std::string name,
                                objects objects,
                                archives archives) {
  // 1. create link step
  auto bin_file = ctx.bin() / name;
  auto& link_step = ctx.add_step(m_cxx, cxx_options(), {})
                        .options({"-o", bin_file.string()})
                        .message(std::format(
                            CXX_LINK, bin_file.relative_path().string()));

  // 2. add object dependencies
  for (auto& obj : objects) {
    link_step.option(obj.object_file.string()).depends_on(*obj.build_step);
  }

  // 3. add library dependencies
  for (auto& ar : archives) {
    link_step.option(ar.archive_file.string()).depends_on(*ar.archive_step);
  }

  return {.binary_file = bin_file, .link_step = &link_step};
}

archive unix_toolchain::ar_cxx(build_ctx& ctx,
                               std::string name,
                               objects objects,
                               archives archives) {
  // 1. create archive step
  auto ar_file = ctx.lib() / std::format("lib{}.a", name);
  auto& ar_step =
      ctx.add_step(m_ar, ar_options({"qc"}), {})
          .options({"-o", ar_file.string()})
          .message(std::format(CXX_AR, ar_file.relative_path().string()));

  // 2. add object dependencies
  for (auto& obj : objects) {
    ar_step.option(obj.object_file.string()).depends_on(*obj.build_step);
  }

  // 3. add library dependencies
  for (auto& ar : archives) {
    ar_step.option(ar.archive_file.string()).depends_on(*ar.archive_step);
  }

  return {.archive_file = ar_file, .archive_step = &ar_step};
}

unix_toolchain& unix_toolchain::set_cxx_standard(cxx_std std) {
  using enum cxx_std;

  int std_num = 0;
  switch (std) {
  case cxx98:
    add_cxx_option("-std=c++98");
    break;
  case cxx11:
    add_cxx_option("-std=c++11");
    break;
  case cxx14:
    add_cxx_option("-std=c++14");
    break;
  case cxx17:
    add_cxx_option("-std=c++17");
    break;
  case cxx20:
    add_cxx_option("-std=c++20");
    break;
  case cxx23:
    add_cxx_option("-std=c++23");
    break;
  case cxx26:
    add_cxx_option("-std=c++26");
    break;
  default:
    throw std::runtime_error("incorrect c++ standard");
  }

  return *this;
}
} // namespace buildxx
