#ifndef BUILDXX_TARGET_HPP
#define BUILDXX_TARGET_HPP

#include "toolchain.hpp"

namespace buildxx {
class build_ctx;
class file_set;
class library;
class shell;

class target : public toolchain {
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

  auto& files(this auto& self, const file_set& files);

  auto& link(this auto& self, library& library) {
    self.m_link.push_back(&library);
    return self;
  }

  auto& depends_on(this auto& self, shell& step) {
    self.first_step().depends_on(step);
    return self;
  }

  auto& build(this auto& self) {
    self.build_steps();
    self.ctx().build_step().depends_on(self.final_step());
    return self;
  }

  virtual shell& first_step() = 0;
  virtual shell& final_step() = 0;

  virtual const path& out_file() const = 0;

  virtual target& build_steps() = 0;

protected:
  build_ctx& ctx();

private:
  build_ctx* m_ctx;

  string m_name;

  vector<library*> m_link;

  vector<path> m_files;
};
} // namespace buildxx

#endif
