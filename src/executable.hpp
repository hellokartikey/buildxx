#ifndef HK_BUILDXX_EXECUTABLE_HPP
#define HK_BUILDXX_EXECUTABLE_HPP

#include "common.hpp"
#include "target.hpp"

namespace buildxx {
class executable : public target {
public:
  using source_files = std::vector<fs::path>;

  executable(build_ctx& ctx, std::string name, fs::path entry);
  ~executable() = default;

  const source_files& sources() const;
  executable& add_source(fs::path file);
  executable& add_source(fs::path prefix, source_files files);

  void create_steps(build_ctx& ctx, toolchain& tc) override;

private:
  source_files m_files{};

  step* m_link_step{};
  std::vector<step*> m_obj_steps{};
};
} // namespace buildxx

#endif
