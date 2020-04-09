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

  DEBUG_RESET_SELECTED();
  assign(matrix, -1);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(matrix(0, 0), -1);
  EXPECT_EQ(matrix(1, 0), -1);
  EXPECT_EQ(matrix(2, 0), -1);

  matrix = 1;

  EXPECT_EQ(matrix(0, 0), +1);
  EXPECT_EQ(matrix(1, 0), +1);
  EXPECT_EQ(matrix(2, 0), +1);
}
