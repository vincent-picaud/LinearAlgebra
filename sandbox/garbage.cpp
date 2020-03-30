#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include "LinearAlgebra/dense/vector.hpp"

using namespace LinearAlgebra;

int
main()
{
  Vector<double> V1(5);
  V1 = 1;

  Tiny_Vector<int, 5> V2;
  V2    = 1;
  V1[2] = 0;

  std::cout << V1 << std::endl;
  std::cout << V2 << std::endl;
  bool status = V1 >= V2;

  std::cout << std::boolalpha << status << std::endl;
}
