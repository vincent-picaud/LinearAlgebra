// [BEGIN_matrix_view]
#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

int
main()
{
  // [DOC]
  //
  // Declares a *static* matrix of dimension $5\times 6$.
  Tiny_Matrix<int, 5, 6> mat;
  mat = 1;

  // [DOC]
  //
  // Create a sub-matrix [1:3,2:5] view and fills it with 1
  auto view_mat = create_matrix_view(mat, 1, 3, 2, 5);
  view_mat      = -1;

  std::cout << "full matrix 1:" << mat << std::endl;

  // [DOC]
  //
  // A static, symmetric matrix of dimension $6\times 6$.
  Tiny_Symmetric_Matrix<int, 6> mat_S;

  // [DOC]
  //
  // Creates a *full* view and fills it with 0
  create_matrix_view_full(mat_S) = 0;  // fill the full matrix

  // [DOC]
  //
  // Here as =mat_S= is symmetric
  // only fills the lower triangular part...
  //
  mat_S = 1;

  // Take a *symmetric* sub-matrix [1:3,1:3] view and fills it with -1
  auto view_mat_S = create_matrix_view(mat_S, 1, 3, 1, 3);
  view_mat_S      = -1;

  std::cout << "full matrix 2:" << create_matrix_view_full(mat_S) << std::endl;
  std::cout << "submatrix   3:" << mat_S << std::endl;
}
// [END_matrix_view]
