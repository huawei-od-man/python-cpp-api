#include "python.h"

class A {};

int add(int i, int j) { return i + j; }

int main(int argc, char const *argv[]) {
  function list_append(&list::append);

  ref list_ref{list{}};
  print(list_ref);
  for (int i = 0; i < 10; ++i) {
    list_append({list_ref, 1});
  }
  print(list_ref);

  function list_size(&list::size);
  print(list_size({list_ref}));

  ref int_ref{1};
  // list_append({int_ref, 1});

  ref func_ref{list_append};

  print("Before");
  func_ref({list_ref, 42});

  print({func_ref, list_ref});


  ref tp = type(list{});
  std::cout << from_ref<typeinfo>(tp).attrs() << std::endl;

  function f(&add);

  function f2([](int i) { return i; });

  std::cout << f2({1}) << std::endl;

  std::cout << f << std::endl;

  print(f({1, 2}));

  // print(f({1, 2, 3}));

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

  // print(A{});

  ref r{"Hello"};
  print(type(r));

  print(type(1) == type(2.0));

  return 0;
}
