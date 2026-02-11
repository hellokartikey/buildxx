#ifndef HK_BUILDXX_TARGET_HPP
#define HK_BUILDXX_TARGET_HPP

#include <vector>

namespace buildxx {
class step;
class build_ctx;
class toolchain;

class target {
public:
  target(build_ctx& ctx);

  template <class T> T& depends_on(this T& self, target& other) {
    self.m_deps.push_back(&other);
    return self;
  }

protected:
  friend build_ctx;
  virtual void create_steps(build_ctx& ctx, toolchain& tc) = 0;

  step& first_step();
  step& final_step();

private:
  std::vector<target*> m_deps;

  step* m_first_step;
  step* m_final_step;
};
} // namespace buildxx

#endif
