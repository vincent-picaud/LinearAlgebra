#include "LinearAlgebra/expr/M0_assign_alpha.hpp"

#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V_assign_alpha, assign)
{
  Tiny_Matrix<int, 3, 1> matrix;
  matrix(0, 0) = 1;
  matrix(1, 0) = 2;
  matrix(2, 0) = 3;

  Expr_Selector_Enum selected = assign(matrix, -1);
  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(matrix(0, 0), -1);
  EXPECT_EQ(matrix(1, 0), -1);
  EXPECT_EQ(matrix(2, 0), -1);

  matrix = 1;

  EXPECT_EQ(matrix(0, 0), +1);
  EXPECT_EQ(matrix(1, 0), +1);
  EXPECT_EQ(matrix(2, 0), +1);
}
