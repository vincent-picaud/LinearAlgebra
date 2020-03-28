#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

int
main()
{
  Matrix<int> M1(10, 10);

  M1 = 0;

  auto M1_view_1 = create_matrix_view(M1, 2, 5, 4, 6);
  //  auto M1_view_2 = create_matrix_view(M1, 6, 8, 4, 6);
  auto M1_view_2 = create_matrix_view(M1, 2, 5, 2, 4);

  M1_view_1 = 1;
  M1_view_2 = 3;

  std::cout << M1;
}
