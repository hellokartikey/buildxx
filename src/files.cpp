#include "buildxx/files.hpp"

#include <ranges>

namespace buildxx {
vector<path> prefix(path dir, vector<string> files) {
  using namespace std::views;
  using namespace std::ranges;
  return files | transform([&](const auto& f) { return dir / f; })
         | to<vector>();
}
} // namespace buildxx
