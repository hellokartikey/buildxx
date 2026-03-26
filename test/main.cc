#include <stdio.h>

#include <foo.hh>

#ifdef TEST
#define PI 3.14
#else
#define PI 3.0
#endif

int main() {
  printf("PI = %f\n", PI);
  printf("foo() = %d\n", foo());
  return 0;
}
