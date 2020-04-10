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

void
test_TODO()
{
  Matrix<int> M1, M0;
  Vector<int> V1;

  V1 = M1 * V1 ;  // <- Generate an error
}

int
main()
{
  test_dot();
  return 0;

  test_dot_return_type();
  return 0;
}
