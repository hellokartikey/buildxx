#ifndef HK_BUILDXX_EXE_HPP
#define HK_BUILDXX_EXE_HPP

#include "common.hpp"
#include "step.hpp"
#include "target.hpp"

namespace bxx {
class exe : public target {
public:
  exe(private_tag, ptr<ctx> ctx, std::string name, fs::path entry);
  ~exe() override = default;

  static ptr<exe> create(ptr<ctx> ctx, std::string name, fs::path entry);

  ptr<exe> add_src(fs::path src);
  ptr<exe> add_src(fs::path prefix, std::vector<std::string> files);

  ptr<target> install() override;

private:
  void add_obj(fs::path entry);

  fs::path src_to_obj(fs::path src);

private:
  ptr<ctx> m_ctx;

  fs::path m_exe;

  std::vector<fs::path> m_files;
  std::vector<ptr<step>> m_steps;

  ptr<step> m_link;
};
} // namespace bxx

#endif
