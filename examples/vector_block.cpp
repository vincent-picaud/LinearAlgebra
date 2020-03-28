#include "LinearAlgebra/vector.hpp"

using namespace LinearAlgebra;

int
main()
{
  Vector<Tiny_Vector<int, 2>> V1(3);

  std::cout << V1 << std::endl;

  std::cout << "================================================================" << std::endl;

  Vector<Vector<int>> V2(3);
  V2[2] = Vector<int>(3);
  Vector<int> v(2);
  v     = 1;
  V2[1] = v;

  std::cout << V2 << std::endl;

  // For the moment compile time error, as we do not support block operations
  //  expr(V2, _assign_, 2);

  std::cout << V2 << std::endl;
}
