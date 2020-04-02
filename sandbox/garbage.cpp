#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

int
main()
{
  using T = float;
  Symmetric_Matrix<T> M(3, 3);
  Vector<T> y(3);
  Tiny_Vector<T, 3> x;

  M(0, 0) = 1;
  //  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;

  M(2, 0) = 1;
  M(2, 1) = 1;
  M(2, 2) = 1;

  x[0] = 1;
  x[1] = 2;
  x[2] = 0;

  auto y_cpy_as_int = create_default_storable(Type_v<int>, y);

  Expr_Selector_Enum selected = assign(y, 2, _identity_, M, x, _plus_, 0, _lhs_);

  //y_cpy_as_int = 2 * transpose(M) * x + 0 * y_cpy_as_int;

  std::cout << M << std::endl;
  std::cout << x << std::endl;

  std::cout << y << std::endl;
  std::cout << y_cpy_as_int << std::endl;

  std::cout << std::boolalpha << (y == y_cpy_as_int) << std::endl;
}
