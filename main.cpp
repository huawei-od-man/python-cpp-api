#include "python.h"

class A {};

int main(int argc, char const *argv[])
{
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
