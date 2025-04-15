#include "ref.h"

#include "bool.h"
#include "box.h"
#include "except.h"
#include "none.h"

const ref None{make_box<NoneType>()};
const ref True{make_box<bool_>(true)};
const ref False{make_box<bool_>(false)};

ref::ref() : ref(None) {}
