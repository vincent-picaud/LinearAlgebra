#include "LinearAlgebra/vector.hpp"

#include <ccomplex>
#include <iostream>

using namespace LinearAlgebra;

int
main()
{
  using T = std::complex<double>;

  Vector<T> V_1(5), V_2(5);

  std::cout << V_1 << std::endl;

  V_2 = V_1;

  std::cout << V_2 << std::endl;
}
