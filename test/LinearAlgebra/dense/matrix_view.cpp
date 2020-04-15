#include "LinearAlgebra/dense/matrix_view.hpp"
#include "LinearAlgebra/expr/matrix_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_View, dynamic_of_static)
{
  Tiny_Matrix<int, 5, 6> mat;
  mat           = 1;
  auto view_mat = create_matrix_view(mat, 1, 3, 2, 5);
  view_mat      = 2;

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
  mat           = 1;
  auto view_mat = create_matrix_view(mat, std::integral_constant<std::size_t, 1>(),
                                     std::integral_constant<std::size_t, 3>(), 2, 5);
  view_mat      = 2;

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
  mat           = 1;
  auto view_mat = create_matrix_view(mat, 1, 3, std::integral_constant<std::size_t, 2>(),
                                     std::integral_constant<std::size_t, 5>());
  view_mat      = 2;

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
  mat           = 1;
  auto view_mat = create_matrix_view(
      mat, std::integral_constant<std::size_t, 1>(), std::integral_constant<std::size_t, 3>(),
      std::integral_constant<std::size_t, 2>(), std::integral_constant<std::size_t, 5>());
  view_mat = 2;

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
  mat                   = 1;
  auto view_mat_mutable = create_matrix_view(mat, std::integral_constant<std::size_t, 1>(),
                                             std::integral_constant<std::size_t, 3>(), 2, 5);
  view_mat_mutable      = 2;

  auto view_mat = create_matrix_view(mat.as_const(), std::integral_constant<std::size_t, 1>(),
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

  M = 1;

  auto M_sut = create_matrix_view_strict_upper_triangular(M);

  M_sut = 2;

  EXPECT_EQ(M(0, 2), 2);
  EXPECT_EQ(M(1, 2), 2);
  EXPECT_EQ(M(2, 2), 1);
}

// Matrix view from raw pointer
//
TEST(Matrix_View, create_matrix_view)
{
  int data[] = {1, 2, 3, 4, 5, 6};

  auto m = create_matrix_view(data, 2, 3);

  m(0, 0) = 10;
  EXPECT_EQ(data[0], 10);

  EXPECT_EQ(m(0, 0), 10);
  EXPECT_EQ(m(1, 0), 2);
  EXPECT_EQ(m(0, 1), 3);
  EXPECT_EQ(m(1, 1), 4);
  EXPECT_EQ(m(0, 2), 5);
  EXPECT_EQ(m(1, 2), 6);

  Matrix<int> M(m.I_size(), m.J_size());

  M = m;

  EXPECT_EQ(M(0, 0), 10);
  EXPECT_EQ(M(1, 0), 2);
  EXPECT_EQ(M(0, 1), 3);
  EXPECT_EQ(M(1, 1), 4);
  EXPECT_EQ(M(0, 2), 5);
  EXPECT_EQ(M(1, 2), 6);
}

TEST(Matrix_View, create_matrix_view_const_version)
{
  const int data[] = {1, 2, 3, 4, 5, 6};

  auto m = create_matrix_view(data, 2, 3);

  // m(0, 0) = 10; <- should not compile
  //
  EXPECT_TRUE((std::is_same_v<const int&, decltype(m(0, 0))>));

  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(1, 0), 2);
  EXPECT_EQ(m(0, 1), 3);
  EXPECT_EQ(m(1, 1), 4);
  EXPECT_EQ(m(0, 2), 5);
  EXPECT_EQ(m(1, 2), 6);

  Matrix<int> M(m.I_size(), m.J_size());

  M = m;

  EXPECT_EQ(M(0, 0), 1);
  EXPECT_EQ(M(1, 0), 2);
  EXPECT_EQ(M(0, 1), 3);
  EXPECT_EQ(M(1, 1), 4);
  EXPECT_EQ(M(0, 2), 5);
  EXPECT_EQ(M(1, 2), 6);
}

TEST(Matrix_View, create_matrix_view_check_size_type)
{
  const int data[] = {1, 2, 3, 4, 5, 6};

  auto m = create_matrix_view(data, std::integral_constant<std::size_t, 2>(), 3);

  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 2>, decltype(m.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::size_t, decltype(m.J_size())>));
  EXPECT_TRUE(
      (std::is_same_v<std::integral_constant<std::size_t, 2>, decltype(m.leading_dimension())>));
}

TEST(Matrix_View, row_view)
{
  Matrix<int> M(3, 5);

  M = 1;

  auto row_view = create_vector_view_matrix_row(M, 1);

  row_view = 2;

  EXPECT_EQ(M(0, 0), 1);
  EXPECT_EQ(M(0, 1), 1);

  EXPECT_EQ(M(1, 0), 2);
  EXPECT_EQ(M(1, 1), 2);

  EXPECT_EQ(M(2, 0), 1);
  EXPECT_EQ(M(2, 1), 1);
}

//
// matrix diagonal view
//
TEST(Matrix_View, diagonal_view_tall)
{
  Matrix<int> M_tall(3, 2);

  int count = 0;
  fill([&count]() { return ++count; }, M_tall);

  auto diag_tall = create_vector_view_matrix_diagonal(M_tall);

  EXPECT_EQ(diag_tall.size(), 2);
  EXPECT_FALSE((Has_Static_Size_v<decltype(diag_tall)>));

  EXPECT_EQ(diag_tall[0], 1);
  EXPECT_EQ(diag_tall[1], 5);
}

TEST(Matrix_View, diagonal_view_wide)
{
  Matrix<int> M_wide(2, 3);

  int count = 0;
  fill([&count]() { return ++count; }, M_wide);

  auto diag_wide = create_vector_view_matrix_diagonal(M_wide);

  EXPECT_EQ(diag_wide.size(), 2);
  EXPECT_FALSE((Has_Static_Size_v<decltype(diag_wide)>));

  EXPECT_EQ(diag_wide[0], 1);
  EXPECT_EQ(diag_wide[1], 4);
}

// static

TEST(Matrix_View, static_diagonal_view_tall)
{
  Tiny_Matrix<int, 3, 2> M_tall;

  int count = 0;
  fill([&count]() { return ++count; }, M_tall);

  auto diag_tall = create_vector_view_matrix_diagonal(M_tall);

  EXPECT_EQ(diag_tall.size(), 2);
  EXPECT_TRUE((Has_Static_Size_v<decltype(diag_tall)>));

  EXPECT_EQ(diag_tall[0], 1);
  EXPECT_EQ(diag_tall[1], 5);
}

TEST(Matrix_View, static_diagonal_view_wide)
{
  Tiny_Matrix<int, 2, 3> M_wide;

  int count = 0;
  fill([&count]() { return ++count; }, M_wide);

  auto diag_wide = create_vector_view_matrix_diagonal(M_wide);

  EXPECT_EQ(diag_wide.size(), 2);
  EXPECT_TRUE((Has_Static_Size_v<decltype(diag_wide)>));

  EXPECT_EQ(diag_wide[0], 1);
  EXPECT_EQ(diag_wide[1], 4);
}

TEST(Matrix_View, from_matrix_to_view)
{
  Tiny_Matrix<int, 2, 3> M;

  M(1, 2) = 10;

  auto view  = create_matrix_view(M);
  view(1, 2) = 1;
  EXPECT_EQ(M(1, 2), 1);
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 2>, decltype(view.I_size())>));
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 3>, decltype(view.J_size())>));
}
