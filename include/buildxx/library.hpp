#ifndef BUILDXX_LIBRARY_HPP
#define BUILDXX_LIBRARY_HPP

#include "target.hpp"

namespace buildxx {
class library : public target, public toolchain {
public:
  library(const string& name);
  ~library() override = default;

  library& shared(bool value);

  library& out_file(const path& file) override;
  const path& out_file() const override;

  library& build_steps() override;

private:
  path m_out_file;
};
} // namespace buildxx

#endif
