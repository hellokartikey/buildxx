#ifndef BUILDXX_UTILS_HPP
#define BUILDXX_UTILS_HPP

#include "types.hpp"

namespace buildxx {
path find_executable(const string& name);

bool create_if_not_exist(const path& p);
} // namespace buildxx

#endif
