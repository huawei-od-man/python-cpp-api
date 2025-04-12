#ifndef STR_H
#define STR_H
#include <string>

#include "ref.h"
#include "object.h"
#include "tuple.h"

class String : public object {
public:
 explicit String(const std::string &str);
 explicit String(const char *c_str);
 ~String() override;

 virtual str format(tuple<> arguments);

 str __str__() override;

private:
 std::string _string;
};

#endif
