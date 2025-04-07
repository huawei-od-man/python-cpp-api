#include "none.h"

#include "bool.h"
#include "str.h"

NoneType* None;

str NoneType::__str__() {
    return new String("None");
}

bool_ NoneType::__bool__() {
  return False;
}
