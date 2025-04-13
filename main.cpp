#include "python.h"

int main() {
  list lst{3.14_f, true, 1_i, "hello"_s};

  std::cout << lst << std::endl;

  list lst2{1, 3, 4, 5, 6};
  std::cout << lst2 << std::endl;

  std::cout << tuple{1, 2, 3} << std::endl;

  std::cout << "This is {} and {} and {}"_s.format(1, 3.11, false) << std::endl;

  std::cout << tuple{1, 2, 3} + tuple{None(), 5, 6} << std::endl;

  auto d = dict{tuple{1, 2}, tuple{3, 4}, tuple{5, 6}};

  std::cout << d << std::endl;

  set s{1, 2, 3, 4, 5};
  std::cout << s << std::endl;

  return 0;
}
