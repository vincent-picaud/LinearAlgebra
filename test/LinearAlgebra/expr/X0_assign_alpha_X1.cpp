#include "LinearAlgebra/expr/X0_assign_alpha_X1.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(X0_Assign_Alpha_X1, vector)
{
  Tiny_Vector<int, 3> v, w;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, 3, v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 3 * 1);
  EXPECT_EQ(w[1], 3 * 2);
  EXPECT_EQ(w[2], 3 * 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, 3, w);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 3 * 3 * 1);
  EXPECT_EQ(w[1], 3 * 3 * 2);
  EXPECT_EQ(w[2], 3 * 3 * 3);
}

TEST(X0_Assign_Alpha_X1, matrix)
{
  Tiny_Matrix<int, 3, 1> v, w;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, 3, v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  EXPECT_EQ(w(0, 0), 3 * 1);
  EXPECT_EQ(w(1, 0), 3 * 2);
  EXPECT_EQ(w(2, 0), 3 * 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, 3, w);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  EXPECT_EQ(w(0, 0), 3 * 3 * 1);
  EXPECT_EQ(w(1, 0), 3 * 3 * 2);
  EXPECT_EQ(w(2, 0), 3 * 3 * 3);
}
