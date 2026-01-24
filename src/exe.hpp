#ifndef HK_BUILDXX_EXE_HPP
#define HK_BUILDXX_EXE_HPP

#include "step.hpp"
#include "target.hpp"

namespace bxx {
class ctx;

class exe : public target {
public:
  exe(private_tag, std::shared_ptr<ctx> ctx, std::string name, fs::path entry);
  ~exe() override = default;

  static std::shared_ptr<exe>
  create(std::shared_ptr<ctx> ctx, std::string name, fs::path entry);

  std::shared_ptr<exe> add_src(fs::path src);
  std::shared_ptr<exe> add_src(fs::path prefix, std::vector<std::string> files);

  std::shared_ptr<target> install() override;

private:
  void add_entry(fs::path entry);

  fs::path src_to_obj(fs::path src);

private:
  std::shared_ptr<ctx> m_ctx;

  std::vector<fs::path> m_files;
  std::vector<std::shared_ptr<step>> m_steps;
  std::shared_ptr<step> m_link;
};
} // namespace bxx

#endif
