#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/expr/matrix_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_View, dynamic_of_static)
{
  Tiny_Matrix<int, 5, 6> mat;
  expr(mat, _assign_, 1);
  auto view_mat = create_view_submatrix(mat, 1, 3, 2, 5);
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
  auto view_mat = create_view_submatrix(mat, std::integral_constant<std::size_t, 1>(),
                                        std::integral_constant<std::size_t, 3>(), 2, 5);
  expr(view_mat, _assign_, 2);

  EXPECT_TRUE((std::is_same_v<int&, decltype(view_mat(0, 0))>));

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
  auto view_mat = create_view_submatrix(mat, 1, 3, std::integral_constant<std::size_t, 2>(),
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
  auto view_mat = create_view_submatrix(
      mat, std::integral_constant<std::size_t, 1>(), std::integral_constant<std::size_t, 3>(),
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
// Const version
TEST(Matrix_View, const_static_of_static_I)
{
  Tiny_Matrix<int, 5, 6> mat;
  expr(mat, _assign_, 1);
  auto view_mat_mutable = create_view_submatrix(mat, std::integral_constant<std::size_t, 1>(),
                                                std::integral_constant<std::size_t, 3>(), 2, 5);
  expr(view_mat_mutable, _assign_, 2);

  auto view_mat = create_view_submatrix(mat.as_const(), std::integral_constant<std::size_t, 1>(),
                                        std::integral_constant<std::size_t, 3>(), 2, 5);

  EXPECT_TRUE((std::is_same_v<const int&, decltype(view_mat(0, 0))>));

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

// Matrix type view
//
TEST(Matrix_View, matrix_view_type)
{
  Matrix<int> M(3, 5);

  expr(M, _assign_, 1);

  auto M_sut = create_view_matrix_type_strict_upper_triangular(M);

  expr(M_sut, _assign_, 2);

  EXPECT_EQ(M(0, 2), 2);
  EXPECT_EQ(M(1, 2), 2);
  EXPECT_EQ(M(2, 2), 1);
}
