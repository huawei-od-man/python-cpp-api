#include "int.h"

#include "ref.h"
#include "tuple.h"
#include "dict.h"
#include "str.h"

ref type(const int_&) {
    static const auto int_type = ::type("int", tuple{}, dict{});
    return int_type;
}
