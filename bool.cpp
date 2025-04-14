#include "bool.h"
#include "ref.h"

bool_::bool_(ref obj) : bool_(obj.operator bool()) {}
