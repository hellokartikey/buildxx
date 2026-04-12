#ifndef BUILDXX_TYPES_HPP
#define BUILDXX_TYPES_HPP

#include <filesystem>
#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace buildxx {
using std::list;
using std::map;
using std::string;
using std::vector;

namespace fs = std::filesystem;
using fs::path;

class error : public std::runtime_error {
public:
  error(const char* err)
      : std::runtime_error(err) {}
  error(const string& err)
      : std::runtime_error(err) {}

  ~error() = default;
};

using namespace std::literals;
} // namespace buildxx

#endif
