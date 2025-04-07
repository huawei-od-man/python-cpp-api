#ifndef FORWARD_H
#define FORWARD_H

class Object;
class Type;
class String;
class Int;
class Float;
class Bool;
class List;
class Tuple;
class Dict;
class Set;
class NoneType;

class Exception;
class NotImplementedError;
class TypeError;
class ValueError;

template <typename T>
class ref;

using object = ref<Object>;
using float_ = ref<Float>;
using bool_ = ref<Bool>;
using int_ = ref<Int>;
using str = ref<String>;

template <typename T = Object>
class list;

template <typename T = Object>
class tuple;

template <typename T = Object>
class set;

template <typename K = Object, typename V = Object>
class dict;

extern NoneType* None;
extern Bool *True, *False;

void python_initialize();

#endif  // FORWARD_H
