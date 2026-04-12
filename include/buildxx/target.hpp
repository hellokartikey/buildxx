#ifndef BUILDXX_TARGET_HPP
#define BUILDXX_TARGET_HPP

#include "toolchain.hpp"

namespace buildxx {
class build_ctx;
class library;
class shell;

class target {
public:
  target(build_ctx& ctx, const string& name);
  virtual ~target() = default;

  const string& name() const;

  auto& file(this auto& self, const path& file) {
    self.m_files.push_back(file);
    return self;
  }

  auto& files(this auto& self, const vector<path>& files) {
    self.m_files.append_range(files);
    return self;
  }

  const vector<path>& files() const;

  auto& depends_on(this auto& self, shell& step) {
    self.first_step().depends_on(step);
    return self;
  }

  auto& build(this auto& self) {
    self.ctx().build_step().depends_on(self.final_step());
    return self;
  }

  shell& first_step();
  shell& final_step();

  virtual const path& out_file() const = 0;
  virtual target& out_file(const path& file) = 0;

  virtual target& build_steps() = 0;

protected:
  build_ctx& ctx();
  const build_ctx& ctx() const;

private:
  build_ctx* m_ctx;

  string m_name;
  vector<path> m_files;

  shell* m_link_step;
  shell* m_first_step;
};
} // namespace buildxx

#endif
