#include "none.h"
#include "box.tcc"

const ref None{make_box<NoneType>()};

ref type(const NoneType &) {
    static const auto NoneType_type = ::type("NoneType", tuple{}, dict{});
    return NoneType_type;
}
