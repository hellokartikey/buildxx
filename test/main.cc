#include <iostream>

#ifdef TEST
#define PI 3.14
#else
#define PI 3
#endif

int main() {
  std::cout << "PI = " << PI << "\n";
  return 0;
}
