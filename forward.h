#ifndef FORWARD_H
#define FORWARD_H

class Exception;
class NotImplementedError;
class TypeError;
class ValueError;
class KeyError;

template <typename T>
class box;
class ref;
class weak_ref;
template <typename T, typename... Args>
ref make_box(Args&&... args);

class object;
class bool_;
class int_;
class float_;
class str;
class list;
class dict;
class dict_items;
class dict_keys;
class dict_values;
class set;
class tuple;
class iterator;
class bytes;
class byte_array;
class NoneType;

using float_type = long double;

#endif  // FORWARD_H
