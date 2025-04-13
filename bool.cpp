#include "bool.h"
#include "ref.h"

bool_::bool_(ref obj) : bool_(static_cast<bool>(*obj)) {}
