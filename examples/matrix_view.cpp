#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

int
main()
{
  Tiny_Matrix<int, 5, 6> mat;

  mat = 1;

  auto view_mat = create_matrix_view(mat, 1, 3, 2, 5);

  view_mat = -1;

  std::cout << mat << std::endl;

  //================

  Tiny_Symmetric_Matrix<int, 6> mat_S;

  mat_S = 1;

  auto view_mat_S = create_matrix_view(mat_S, 1, 3, 1, 3);

  view_mat_S = -1;

  std::cout << create_matrix_view_full(mat_S) << std::endl;
  std::cout << mat_S << std::endl;
}
