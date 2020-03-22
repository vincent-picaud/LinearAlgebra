#include "LinearAlgebra/matrix.hpp"

using namespace LinearAlgebra;

int
main()
{
  Tiny_Matrix<int, 5, 6> mat;

  expr(mat, _assign_, 1);
  auto view_mat = create_view(mat, 1, 3, 2, 5);

  expr(view_mat, _assign_, -1);

  std::cout << mat << std::endl;

  //================

  Tiny_Symmetric_Matrix<int, 6> mat_S;

  expr(mat_S, _assign_, 1);

  auto view_mat_S = create_view(mat_S, 1, 3, 1, 3);

  expr(view_mat_S, _assign_, -1);

  std::cout << create_view_full(mat_S) << std::endl;
  std::cout << mat_S << std::endl;
}
