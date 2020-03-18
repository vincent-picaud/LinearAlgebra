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

  Tiny_Matrix<T, 5, 2> M;
  Vector<T> y(5), x(2);

  //  expr(y, _assign_, 1, _identity_, M, x, _plus_, 2, _vector_0_);

#if (HAS_BLAS)
  expr(y, _assign_, 1, _vector_0_, _plus_, 2, _identity_, M, x);
  //  expr(y, _assign_, 1, _conjugate_, M, x, _plus_, 2, _vector_0_);
#else
  assert(0 && "Not implemented yet");
#endif

  std::cout << y;
}
