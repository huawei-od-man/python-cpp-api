#include "python.h"

int main() {
    list lst;
    lst.append(true);
    std::cout << make_box<list>(lst) << std::endl;
    std::cout << lst << std::endl;

    std::cout << "This is {} and {} and {}"_s.format(1, 3.11, false)
     << std::endl;

    return 0;
}
