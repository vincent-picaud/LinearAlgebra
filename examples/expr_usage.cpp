#include "LinearAlgebra/vector.hpp"

#include <iostream>

using namespace LinearAlgebra;

int
main()
{
  Vector<double> V_1(5), V_2(5);

  std::cout << V_1 << std::endl;

  expr(V_2, _assign_, V_1);

  std::cout << V_2 << std::endl;
}
