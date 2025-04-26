#include "none.h"
#include "ref.tcc"
#include "tuple.h"
#include "dict.h"

const ref None{make_box<NoneType>()};
