#include "python.h"

int main(int argc, char const *argv[])
{
  function<int(int, int)> f = [](int a, int b) {
    return a + b;
  };
  ref res = f(tuple{1, 2});
  std::cout << f;

  return 0;
}
