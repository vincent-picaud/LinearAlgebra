#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

int
main()
{
  Tiny_Matrix<int, 5, 6> mat;

  mat = 1;

  auto view_mat = create_matrix_view(mat, 1, 3, 2, 5);

  view_mat = -1;

  std::cout << "full matrix:" << mat << std::endl;

  //================

  Tiny_Symmetric_Matrix<int, 6> mat_S;

  create_matrix_view_full(mat_S) = 0;  // fill the full matrix

  mat_S = 1;  // here as mat_S is symmetric
              // only fill lower triangular part is filled

  // Take a subview of a _symmetric matrix_
  auto view_mat_S = create_matrix_view(mat_S, 1, 3, 1, 3);

  view_mat_S = -1;  // here the subview mat_S is symmetric too and
                    // only the lower triangular part will be filled

  std::cout << "full matrix:" << create_matrix_view_full(mat_S) << std::endl;
  std::cout << "submatrix:" << mat_S << std::endl;
}
