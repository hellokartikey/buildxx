#ifndef BUILDXX_SHELL_HPP
#define BUILDXX_SHELL_HPP

#include <mutex>

#include <boost/cobalt/task.hpp>

#include "types.hpp"

namespace buildxx {
using boost::cobalt::task;

class shell {
public:
  static constexpr int RC_OK = 0;
  static constexpr int RC_NULL = -1;

  shell& bin(const char* exe);
  shell& bin(const string& exe);
  shell& bin(const path& exe);

  shell& env(const string& key, const string& value);

  shell& flag(const string& arg);
  shell& flags(const vector<string>& args);

  shell& message(const string& msg);

  shell& depends_on(shell& other);

  task<int> exec(bool verbose = false);
  int rc() const;

  bool is_ok() const;
  bool is_phony() const;
  bool is_nop() const;

  const vector<path>& in_files() const;
  shell& in_file(path file);
  shell& in_files(const vector<path>& files);

  const path& out_file() const;
  shell& out_file(path file);

private:
  int m_rc = RC_NULL;

  std::mutex m_mutex;

  path m_exe;
  vector<string> m_args;
  map<string, string> m_env;

  string m_msg;

  vector<shell*> m_depends;

  vector<path> m_in_files;
  path m_out_file;
  bool m_is_phony = true;
  bool m_nop = true;
};
} // namespace buildxx

#endif
