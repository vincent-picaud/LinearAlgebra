#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/expr/matrix_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_View, dynamic_of_static)
{
  Tiny_Matrix<int, 5, 6> mat;
  expr(mat, _assign_, 1);
  auto view_mat = view(mat, 1, 3, 2, 5);
  expr(view_mat, _assign_, 2);

  // EXPECT_TRUE((std::is_same_v<std::size_t, typename decltype(view_mat)::size_type>));
  EXPECT_EQ(view_mat.I_size(), 2);
  EXPECT_EQ(view_mat.J_size(), 3);

  EXPECT_EQ(mat(0, 2), 1);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 1), 1);

  EXPECT_EQ(mat(2, 5), 1);
  EXPECT_EQ(mat(2, 4), 2);
  EXPECT_EQ(mat(3, 4), 1);
}

TEST(Matrix_View, static_of_static_I)
{
  Tiny_Matrix<int, 5, 6> mat;
  expr(mat, _assign_, 1);
  auto view_mat = view(mat, std::integral_constant<std::size_t, 1>(),
                       std::integral_constant<std::size_t, 3>(), 2, 5);
  expr(view_mat, _assign_, 2);

  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 2>,
                              typename decltype(view_mat)::I_size_type>));
  EXPECT_TRUE((std::is_same_v<std::size_t, typename decltype(view_mat)::J_size_type>));

  EXPECT_EQ(view_mat.I_size(), 2);
  EXPECT_EQ(view_mat.J_size(), 3);

  EXPECT_EQ(mat(0, 2), 1);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 1), 1);

  EXPECT_EQ(mat(2, 5), 1);
  EXPECT_EQ(mat(2, 4), 2);
  EXPECT_EQ(mat(3, 4), 1);
}

TEST(Matrix_View, static_of_static_J)
{
  Tiny_Matrix<int, 5, 6> mat;
  expr(mat, _assign_, 1);
  auto view_mat = view(mat, 1, 3, std::integral_constant<std::size_t, 2>(),
                       std::integral_constant<std::size_t, 5>());
  expr(view_mat, _assign_, 2);

  EXPECT_TRUE((std::is_same_v<std::size_t, typename decltype(view_mat)::I_size_type>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 3>,
                              typename decltype(view_mat)::J_size_type>));

  EXPECT_EQ(view_mat.I_size(), 2);
  EXPECT_EQ(view_mat.J_size(), 3);

  EXPECT_EQ(mat(0, 2), 1);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 1), 1);

  EXPECT_EQ(mat(2, 5), 1);
  EXPECT_EQ(mat(2, 4), 2);
  EXPECT_EQ(mat(3, 4), 1);
}

TEST(Matrix_View, static_of_static_IJ)
{
  Tiny_Matrix<int, 5, 6> mat;
  expr(mat, _assign_, 1);
  auto view_mat =
      view(mat, std::integral_constant<std::size_t, 1>(), std::integral_constant<std::size_t, 3>(),
           std::integral_constant<std::size_t, 2>(), std::integral_constant<std::size_t, 5>());
  expr(view_mat, _assign_, 2);

  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 2>,
                              typename decltype(view_mat)::I_size_type>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 3>,
                              typename decltype(view_mat)::J_size_type>));

  EXPECT_EQ(view_mat.I_size(), 2);
  EXPECT_EQ(view_mat.J_size(), 3);

  EXPECT_EQ(mat(0, 2), 1);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 2), 2);
  EXPECT_EQ(mat(1, 1), 1);

  EXPECT_EQ(mat(2, 5), 1);
  EXPECT_EQ(mat(2, 4), 2);
  EXPECT_EQ(mat(3, 4), 1);
}
