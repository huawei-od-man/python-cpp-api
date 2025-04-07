#include "float.h"
#include "str.h"

Float::Float(double value) : _value(value) {}

Float::~Float()  = default;

str Float::__str__() {
    return new String(std::to_string(_value));
}

float_ Float::__float__() { return this; }


float_ operator""_F(long double value) {
    return new Float{static_cast<double>(value)};
}
