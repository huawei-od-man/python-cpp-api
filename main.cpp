#include "python.h"

int main(int argc, char const *argv[])
{
  ref r{false};

  std::cout << r << std::endl;
  std::cout << from_ref<int>(r);

  return 0;
}
