#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

template <typename T>
void
print(const T&)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

void
test_dot()
{
  Vector<double> V1(5);
  Vector<double> V2(5);

  V1 = 2;
  V2 = 3;

  dot(V1, V2);  //  5 * 2 * 3
}

void
test_dot_return_type()
{
  Vector<std::complex<float>> V1(5);
  V1 = std::complex<float>(3, 2);

  auto Z = dot(V1, V1);

  print(Z);
}

int
main()
{
  //  test_dot();
  test_dot_return_type();
  return 0;

  using T = float;
  Symmetric_Matrix<T> M(3, 3);
  Vector<T> y(3), y2(3);
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

  assign(y, 2, _identity_, M, x, _plus_, 0, _lhs_);

  y2 = 2 * M * x;

  std::cout << M << std::endl;
  std::cout << x << std::endl;

  std::cout << y << std::endl;
  std::cout << y2 << std::endl;

  std::cout << std::boolalpha << (y == y2) << std::endl;
}
