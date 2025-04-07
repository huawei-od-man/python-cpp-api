#include "object.h"

#include "except.h"

Object::Object() : _ref_count(0) {}

void Object::add_ref() {
    _ref_count.fetch_add(1, std::memory_order_relaxed);
}

void Object::dec_ref() {
    _ref_count.fetch_sub(1, std::memory_order_relaxed);
}

void Object::release() { delete this; }

int32_t Object::ref_count() const {
    return _ref_count.load(std::memory_order_relaxed);
}

bool_ Object::__bool__() {
    throw NotImplementedError("Object::__bool__");
}
