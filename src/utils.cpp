#include "buildxx/utils.hpp"

#include <boost/process/environment.hpp>

namespace buildxx {
namespace env = boost::process::environment;

path find_executable(const string& name) { return env::find_executable(name); }

bool create_if_not_exist(const path& p) {
  if (fs::is_directory(p)) {
    return false;
  }

  return fs::create_directories(p);
}
} // namespace buildxx
