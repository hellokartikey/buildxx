#include "unix_toolchain.hpp"

#include "build_ctx.hpp"

namespace buildxx {
unix_toolchain::unix_toolchain(std::string prefix)
    : toolchain() {
  m_cc = env::find_executable(prefix + "cc");
  m_cxx = env::find_executable(prefix + "c++");
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
          .add_option("-c")
          .add_option(src.string())
          .add_option({"-o", obj_file.string()})
          .add_message(std::format("Building C++ object {}",
                                   fs::relative(obj_file).string()));

  return {.object_file = obj_file,
          .source_file = src_file,
          .build_step = &build_step};
}

binary
unix_toolchain::link_cxx(build_ctx& ctx, std::string name, objects objects) {
  auto bin_file = ctx.bin() / name;
  auto& link_step = ctx.add_step(m_cxx, cxx_options(), {})
                        .add_option({"-o", bin_file.string()});

  for (auto& obj : objects) {
    link_step.add_option(obj.object_file.string())
        .depends_on(*obj.build_step)
        .add_message(std::format("Linking C++ executable {}", name));
  }

  return {.binary_file = bin_file,
          .object_files = objects,
          .link_step = &link_step};
}
} // namespace buildxx
