#include "object.h"

#include "except.h"

object::object() : _ref_count(0) {}

void object::add_ref() {
    _ref_count.fetch_add(1, std::memory_order_relaxed);
}

void object::dec_ref() {
    _ref_count.fetch_sub(1, std::memory_order_relaxed);
}

void object::release() { delete this; }

int32_t object::ref_count() const {
    return _ref_count.load(std::memory_order_relaxed);
}

bool_ object::__bool__() {
    throw NotImplementedError("Object::__bool__");
}
