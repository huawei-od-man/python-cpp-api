#ifndef PYTHONCPPAPI_FORWARD_H
#define PYTHONCPPAPI_FORWARD_H

template <typename T>
class ref;

class Object;
class Str;

using object = ref<Object>;
using str = ref<Str>;

#endif
