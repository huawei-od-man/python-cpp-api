#ifndef FORWARD_H
#define FORWARD_H
#include <type_traits>
#include <iosfwd>

struct Any;
class ref;
class weak_ref;

template <typename T>
ref to_ref(T&& value);

template <typename T>
std::conditional_t<std::is_scalar_v<T>, T, T&> from_ref(ref& r);

template <typename T>
std::conditional_t<std::is_scalar_v<T>, T, const T&> from_ref(const ref& r);

template <typename T>
class box;

template <typename T, typename... Args>
ref make_box(Args&&... args);

class typeinfo;
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
template <typename F>
class function;

template <typename T>
ref type(const T&);

ref type(const ref&);

ref type(const str& name, const tuple& bases, const dict& attrs);

ref type(const typeinfo&);
ref type(const str&);
ref type(const bool_&);
ref type(const float_&);
ref type(const int_&);
ref type(const object&);
ref type(const dict&);
ref type(const list&);
ref type(const set&);
ref type(const NoneType&);
ref type(const tuple&);

str repr(const object& value);

extern const ref None, True, False;

class Exception;
class NotImplementedError;
class TypeError;
class ValueError;
class KeyError;


#endif  // FORWARD_H
