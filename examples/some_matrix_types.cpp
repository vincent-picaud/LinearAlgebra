#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <iostream>

using namespace LinearAlgebra;

int
main()
{
  Matrix<double> M_1(4, 5);

  Symmetric_Matrix<int> M_2(4, 4);

  Tiny_Lower_Triangular_Strict_Matrix<float, 4, 7> M_3;

  std::cout << M_1 << std::endl;
  std::cout << M_2 << std::endl;
  std::cout << M_3 << std::endl;
}
