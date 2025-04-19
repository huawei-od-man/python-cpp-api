#include "type.h"

#include "object.h"

#include "box.tcc"

typeinfo::typeinfo(const str& name, const tuple& bases, const dict& attrs
) : _name(name), _bases(bases), _attrs(attrs) {}

ref type(const str& name, const tuple& bases, const dict& attrs) {
  return make_box<typeinfo>(name, bases, attrs);
}

ref type(const ref& obj) { return obj->type(); }

ref type(const typeinfo&) {
  static const auto type_type = type("type", {}, {});
  return type_type;
}
