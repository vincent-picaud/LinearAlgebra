#include "LinearAlgebra/expr/copy_matrix.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_view.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(M_assign_M, copy)
{
  Tiny_Matrix<int, 3, 2> mat_1;
  mat_1(0, 1) = 1;
  mat_1(1, 1) = 2;
  mat_1(2, 1) = 3;
  Matrix<int> mat_2(3, 2);
  mat_2(0, 1) = 0;
  mat_2(1, 1) = 0;
  mat_2(2, 1) = 0;

  DEBUG_RESET_SELECTED();
  assign(mat_2, mat_1);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(mat_1(0, 1), 1);
  EXPECT_EQ(mat_1(1, 1), 2);
  EXPECT_EQ(mat_1(2, 1), 3);

  EXPECT_EQ(mat_2(0, 1), 1);
  EXPECT_EQ(mat_2(1, 1), 2);
  EXPECT_EQ(mat_2(2, 1), 3);
}

TEST(M_assign_M, copy_assert)
{
  Tiny_Matrix<int, 3, 1> mat_1;
  DEBUG_RESET_SELECTED();
  assign(mat_1, mat_1);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::END);  // "nothing to do" detected
}

TEST(M_assign_M, copy_assert_2)
{
  Tiny_Matrix<int, 3, 2> mat_1;
  Tiny_Matrix<int, 2, 2> mat_2;
  EXPECT_DEBUG_DEATH(assign(mat_1, mat_2), "");  // Bad dimensions
}

TEST(M_assign_M, overloaded_operator)
{
  Tiny_Matrix<int, 3, 1> v;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;
  Matrix<int> w(3, 1);
  w(0, 0) = 0;
  w(1, 0) = 0;
  w(2, 0) = 0;

  w = v;

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  EXPECT_EQ(w(0, 0), 1);
  EXPECT_EQ(w(1, 0), 2);
  EXPECT_EQ(w(2, 0), 3);
}

// Note: fundamental to understand to properly use this library!
//
TEST(M_assign_M, copy_semantic)
{
  int data[5] = {1, 2, 3, 4, 5};
  int data_2[5];

  // Construction from the raw type
  auto view = create_matrix_view(data, 5, 1);

  Matrix<int> v_cpy(5, 1);

  v_cpy = view;
  EXPECT_EQ(v_cpy(0, 0), 1);
  EXPECT_EQ(v_cpy(1, 0), 2);
  EXPECT_EQ(v_cpy(2, 0), 3);
  EXPECT_EQ(v_cpy(3, 0), 4);
  EXPECT_EQ(v_cpy(4, 0), 5);

  auto view_2 = create_matrix_view(data_2, 5, 1);

  EXPECT_EQ(view_2.data(), data_2);
  view_2 = view;                     // Here a deep copy! (SAME semantic as storable v_cpy)
  EXPECT_EQ(view_2.data(), data_2);  // and NOT a simple pointer copy!
  EXPECT_EQ(view.data(), data);

  EXPECT_EQ(view_2(0, 0), 1);
  EXPECT_EQ(view_2(1, 0), 2);
  EXPECT_EQ(view_2(2, 0), 3);
  EXPECT_EQ(view_2(3, 0), 4);
  EXPECT_EQ(view_2(4, 0), 5);

  //================

  v_cpy(2, 0) = 30;

  view_2 = v_cpy;  // also a deep copy here

  EXPECT_EQ(view_2.data(), data_2);
  EXPECT_EQ(view_2(0, 0), 1);
  EXPECT_EQ(view_2(1, 0), 2);
  EXPECT_EQ(view_2(2, 0), 30);
  EXPECT_EQ(view_2(3, 0), 4);
  EXPECT_EQ(view_2(4, 0), 5);
}
