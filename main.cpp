#include "python.h"

class A {};

int add(int i, int j) { return i + j;
}
int main(int argc, char const *argv[])
{
  function f(&add);

  std::cout << f << std::endl;

  print(f({1, 2}));

  print(f({1, 2, 3}));

  tuple t{1, 2, 3};

  print(hash(t));
  print(hash(None));
  print(hash(type(1)));
  print(type(1)->hash());

  print(type(1));
  print(type(type(1)));
  print(type(false));

  print(type(None));
  print(type(False));

  print(A{});

  ref r{"Hello"};
  print(type(r));

  print(type(1) == type(2.0));

  int res = from_ref<int>(r());



  return 0;
}
