#include "LinearAlgebra/expr/M_assign_M.hpp"

#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(M_assign_M, copy)
{
  Tiny_Matrix<int, 3, 2> mat_1;
  mat_1(0,1) = 1;
  mat_1(1,1) = 2;
  mat_1(2,1) = 3;
  Matrix<int> mat_2(3, 2);
  mat_2(0,1) = 0;
  mat_2(1,1) = 0;
  mat_2(2,1) = 0;

  Expr_Selector_Enum selected = assign(mat_2, mat_1);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(mat_1(0,1), 1);
  EXPECT_EQ(mat_1(1,1), 2);
  EXPECT_EQ(mat_1(2,1), 3);

  EXPECT_EQ(mat_2(0,1), 1);
  EXPECT_EQ(mat_2(1,1), 2);
  EXPECT_EQ(mat_2(2,1), 3);
}

TEST(M_assign_M, copy_assert)
{
  Tiny_Matrix<int, 3, 1> mat_1;
  EXPECT_DEBUG_DEATH(assign(mat_1, mat_1), "");
}

TEST(M_assign_M, copy_assert_2)
{
  Tiny_Matrix<int, 3, 2> mat_1;
  Tiny_Matrix<int, 2, 2> mat_2;
  EXPECT_DEBUG_DEATH(assign(mat_1, mat_2), "");
}
