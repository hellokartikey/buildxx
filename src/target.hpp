#ifndef HK_BUILDXX_TARGET_HPP
#define HK_BUILDXX_TARGET_HPP

#include <string>
#include <vector>

namespace buildxx {
class step;
class build_ctx;
class toolchain;

class target {
public:
  target(build_ctx& ctx, std::string name);
  virtual ~target() = default;

  // cannot be copied
  target(const target&) = delete;
  target& operator=(const target&) = delete;

  // can be moved
  target(target&&) = default;
  target& operator=(target&&) = default;

  template <class T> T& depends_on(this T& self, target& other) {
    self.m_deps.push_back(&other);
    self.first_step().depends_on(other.final_step());
    return self;
  }

  const std::string& name() const;

protected:
  friend build_ctx;

  void create_steps_with_deps(build_ctx& ctx, toolchain& tc);
  virtual void create_steps(build_ctx& ctx, toolchain& tc) = 0;

  step& final_step();

private:
  step& first_step();

private:
  std::vector<target*> m_deps{};

  std::string m_name;

  step* m_first_step{};
  step* m_final_step{};

  bool m_steps_created = false;
};
} // namespace buildxx

#endif
