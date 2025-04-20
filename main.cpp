#include "python.h"

class A {};

int main(int argc, char const *argv[])
{
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
