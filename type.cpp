#include "type.h"

#include "box.h"
#include "function.h"

ref type(const str& name, const tuple& bases, const dict& attrs) {
  return to_ref(typeinfo{
      .name = name,
      .bases = bases,
      .attrs = attrs,
  });
}

ref type(ref obj) { return obj->type(); }

template <>
ref type<typeinfo>() {
  static const auto type_type = to_ref(typeinfo{
      .name = "type",
      .bases = tuple{type<object>()},
  });

  return type_type;
}
