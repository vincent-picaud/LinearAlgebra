#include "LinearAlgebra/expr/X_eq_neg_X.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(X_eq_neg_X, vector)
{
  Tiny_Vector<double, 2> V, W;
  V = 1;

  DEBUG_RESET_SELECTED();
  assign(W, _unary_minus_, V);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(W[0], -V[0]);
  EXPECT_EQ(W[1], -V[1]);
}

TEST(X_eq_neg_X, matrix)
{
  Tiny_Matrix<double, 2, 2> V, W;
  V = 1;

  DEBUG_RESET_SELECTED();
  assign(W, _unary_minus_, V);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(W(0, 0), -V(0, 0));
  EXPECT_EQ(W(0, 1), -V(0, 1));
  EXPECT_EQ(W(1, 0), -V(1, 0));
  EXPECT_EQ(W(1, 1), -V(1, 1));
}
