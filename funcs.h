#ifndef FUNCS_H
#define FUNCS_H
#include <initializer_list>
#include <iostream>

#include "forward.h"
#include "ref.h"

void print(std::initializer_list<Any> args, std::ostream& os = std::cout);
void print(Any arg, std::ostream& os = std::cout);

#endif  // FUNCS_H
