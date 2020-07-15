#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/expr/X0_eq_aX1_X2.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

//
// Vector
//
TEST(X0_assign_alpha_X1_plus_X0, vector_generic)
{
  Tiny_Vector<int, 3> v;
  Vector<int> w(3);

  iota(v, 1);
  iota(w, 5);

  DEBUG_RESET_SELECTED();
  assign(v, _plus_, _product_, Scalar(2), w, v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1 + 2 * w[0]);
  EXPECT_EQ(v[1], 2 + 2 * w[1]);
  EXPECT_EQ(v[2], 3 + 2 * w[2]);
}

TEST(X0_assign_alpha_X1_plus_X0, vector_generic_alias)
{
  Tiny_Vector<int, 3> v;
  Vector<int> w(3);

  iota(v, 1);
  iota(w, 5);

  DEBUG_RESET_SELECTED();
  assign(v, _plus_, _product_, Scalar(2), w, v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1 + 2 * w[0]);
  EXPECT_EQ(v[1], 2 + 2 * w[1]);
  EXPECT_EQ(v[2], 3 + 2 * w[2]);
}

//
// Matrix
//
TEST(X0_assign_alpha_X1_plus_X0, matrix_generic_alias)
{
  Tiny_Matrix<int, 3, 1> v;
  Matrix<int> w(3, 1);

  v = 1;
  w = 5;

  DEBUG_RESET_SELECTED();
  assign(v, _plus_, _product_, Scalar(2), w, v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v(1, 0), 1 + 2 * 5);
}
