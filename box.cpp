#include "box.h"

#include "box.tcc"

template class box<str>;
template class box<bool_>;
template class box<int_>;
template class box<float_>;
template class box<list>;
template class box<dict>;
template class box<set>;
template class box<NoneType>;
template class box<tuple>;
