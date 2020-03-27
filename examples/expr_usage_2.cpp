#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <ccomplex>
#include <iostream>

using namespace LinearAlgebra;
 
int
main()
{
  //  using T = std::complex<double>;
  using T = double;

  Tiny_Matrix<T, 3, 2> M;
  Vector<T> y(3);
  Tiny_Vector<T, 2> x;

  M(0, 0) = 1;
  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;
  M(2, 0) = 1;
  M(2, 1) = 1;

  x[0] = 1;
  x[1] = 2;
  //  expr(y, _assign_, 1, _identity_, M, x, _plus_, 2, _vector_0_);

#if (HAS_BLAS)
  //expr(y, _assign_, 0, _vector_0_, _plus_, 2, _identity_, M, x);
    expr(y, _assign_, 2, _identity_, M, x, _plus_, 0, _vector_0_);
#else
  assert(0 && "Not implemented yet");
#endif

  std::cout << y << std::endl;
  std::cout << M << std::endl;
  std::cout << x << std::endl;

  std::cout << "y =" << y[0] << " " << y[1] << " " << y[2] << std::endl;
  std::cout << "x =" << x[0] << " " << x[1] << std::endl;
  assert(y[0] == 2 * x[0]);
  assert(y[1] == 2 * x[1]);
  assert(y[2] == 2 * (x[0] + x[1]));
}
