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

class object;
class bool_;
class int_;
class float_;
class str;
class none;
class list;
class dict;
class set;
class tuple;


extern NoneType* None;
extern Bool *True, *False;

void python_initialize();

#endif  // FORWARD_H
