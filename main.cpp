#include "python.h"

class MyClass {
public:
 virtual ~MyClass() = default;
};

int main() {
  ref r{"hello"};
  ref s{123};
  ref t{3.14f};
  ref u{list{1, 2, 3}};
  ref v{dict{{"key", "value"}}};
  ref w{set{1, 2, 3}};
  ref x{tuple{1, 2, 3}};
  ref y{None};
  ref z{True};
  ref a{False};
  ref b{MyClass{}};

  print(u);
  print("The type of r is {}"_s.format(r->type()));

  print("{}, type is {}"_s.format(r, r->type()));
  print("{}, type is {}"_s.format(s, s->type()));
  print("{}, type is {}"_s.format(t, t->type()));
  print("{}, type is {}"_s.format(u, u->type()));
  print("{}, type is {}"_s.format(v, v->type()));
  print("{}, type is {}"_s.format(w, w->type()));
  print("{}, type is {}"_s.format(x, x->type()));
  print("{}, type is {}"_s.format(y, y->type()));
  print("{}, type is {}"_s.format(z, z->type()));
  print("{}, type is {}"_s.format(a, a->type()));
  print("{}, type is {}"_s.format(b, b->type()));
  
  return 0;
}
