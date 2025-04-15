#include "python.h"

class MyClass {
public:
 virtual ~MyClass() = default;
};

int main() {
  ref r = MyClass();
  print({"this is", 1, r->type()});

  return 0;
}
