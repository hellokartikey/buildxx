#ifndef BUILDXX_TYPES_HPP
#define BUILDXX_TYPES_HPP

#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/cobalt.hpp>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

namespace buildxx {
using std::list;
using std::map;
using std::string;
using std::vector;

namespace fs = boost::filesystem;
using fs::path;

namespace asio = boost::asio;

namespace co = boost::cobalt;
using co::promise;
using co::task;

namespace proc = boost::process;
namespace env = proc::environment;

class error : public std::runtime_error {
public:
  error(const char* err)
      : std::runtime_error(err) {}
  ~error() = default;
};
} // namespace buildxx

#endif
