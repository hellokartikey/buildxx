#ifndef HK_BUILDXX_EXECUTABLE_HPP
#define HK_BUILDXX_EXECUTABLE_HPP

#include "common.hpp"
#include "target.hpp"

namespace buildxx {
class executable : public target {
public:
  using source_files = std::vector<fs::path>;

  executable(build_ctx& ctx, std::string name);
  ~executable() override = default;

  const source_files& get_sources() const;
  executable& source(fs::path file);
  executable& sources(source_files files);
  executable& sources(fs::path prefix, source_files files);

private:
  void create_steps(build_ctx& ctx, toolchain& tc) override;

private:
  source_files m_files{};

  step* m_link_step{};
  std::vector<step*> m_obj_steps{};
};
} // namespace buildxx

#endif
