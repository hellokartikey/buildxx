#ifndef HK_BUILDXX_TC_HPP
#define HK_BUILDXX_TC_HPP

#include <memory>

#include "common.hpp"

namespace bxx {
class tc : public std::enable_shared_from_this<tc> {
public:
  struct private_tag {};

  tc(private_tag) {}
  virtual ~tc() = default;

  virtual const fs::path& cxx() const = 0;
  virtual const fs::path& cc() const = 0;
  virtual const fs::path& ld() const = 0;

  ptr<tc> add_cxx_opt(std::string opt);
  ptr<tc> add_cc_opt(std::string opt);
  ptr<tc> add_ld_opt(std::string opt);

  ptr<tc> add_cxx_opts(std::vector<std::string> opts);
  ptr<tc> add_cc_opts(std::vector<std::string> opts);
  ptr<tc> add_ld_opts(std::vector<std::string> opts);

  std::vector<std::string> cxx_opts(std::vector<std::string> opts = {}) const;
  std::vector<std::string> cc_opts(std::vector<std::string> opts = {}) const;
  std::vector<std::string> ld_opts(std::vector<std::string> opts = {}) const;

private:
  template <class T> ptr<T> get(this T& self) {
    return self.shared_from_this();
  }

private:
  std::vector<std::string> m_cxx_opts;
  std::vector<std::string> m_cc_opts;
  std::vector<std::string> m_ld_opts;
};
} // namespace bxx

#endif
