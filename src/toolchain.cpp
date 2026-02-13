#include "toolchain.hpp"

namespace buildxx {
objects toolchain::build_cxx(build_ctx& ctx, std::vector<fs::path> sources) {
  objects ret;

  for (auto& source : sources) {
    ret.push_back(build_cxx(ctx, source));
  }

  return ret;
}

objects toolchain::build_cxx_shared(build_ctx& ctx,
                                    std::vector<fs::path> sources) {
  objects ret;

  for (auto& source : sources) {
    ret.push_back(build_cxx_shared(ctx, source));
  }

  return ret;
}

step::arguments toolchain::cxx_options(step::arguments flags) {
  flags.append_range(m_cxx_flags);
  flags.append_range(m_cxx_define);
  flags.append_range(m_cxx_include);

  return flags;
}

step::arguments toolchain::ar_options(step::arguments flags) {
  flags.append_range(m_ar_opts);
  return flags;
}
} // namespace buildxx
