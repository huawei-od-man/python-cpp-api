#include "str.h"

String::String(const char *c_str) : _string(c_str) {}

String::~String() = default;

str String::__str__() { return ref<String>(this); }
