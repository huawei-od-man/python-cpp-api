#include "none.h"
#include "ref.h"
#include "box.h"

ref None() {
  return make_box<NoneType>();
}
