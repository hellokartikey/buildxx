#ifndef HK_BUILDXX_LIBRARY_HPP
#define HK_BUILDXX_LIBRARY_HPP

#include "code.hpp"
#include "target.hpp"
#include "toolchain.hpp"

namespace buildxx {
class library : public target, public code_mixin {
public:
  library(build_ctx& ctx, std::string name);
  ~library() override = default;

  enum link get_linkage() const;
  library& linkage(enum link type);

  const std::optional<archive>& artifact() const;

private:
  void create_steps(build_ctx& ctx, toolchain& tc) override;

private:
  enum link m_link = link::archive;
  std::optional<archive> m_archive;
};
} // namespace buildxx

#endif
