#ifndef BUILDXX_FILES_HPP
#define BUILDXX_FILES_HPP

#include "types.hpp"

namespace buildxx {
vector<path> glob(string pattern);
vector<path> prefix(path dir, vector<string> files);
} // namespace buildxx

#endif
