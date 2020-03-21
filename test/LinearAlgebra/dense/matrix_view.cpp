#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/expr/matrix_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_View, dynamic_of_static)
{
  Tiny_Matrix<int, 5,6> mat;
  expr(mat, _assign_, 1);
  auto view_mat = view(mat, 1, 3);
  expr(view_mat, _assign_, 2);

  // EXPECT_TRUE((std::is_same_v<std::size_t, typename decltype(view_mat)::size_type>));
  // EXPECT_EQ(view_mat.size(), 2);

  // EXPECT_EQ(mat[0], 1);
  // EXPECT_EQ(mat[1], 2);
  // EXPECT_EQ(mat[2], 2);
  // EXPECT_EQ(mat[3], 1);
}
