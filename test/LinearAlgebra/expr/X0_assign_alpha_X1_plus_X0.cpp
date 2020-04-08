#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_V1_plus_V0.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/expr/M0_assign_alpha_M1_plus_M0.hpp"

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

  Expr_Selector_Enum selected = assign(v, _plus_, _product_, 2, w, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);
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

  Expr_Selector_Enum selected = assign(v, _plus_, _product_, 2, w, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);
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

  Expr_Selector_Enum selected = assign(v, _plus_, _product_, 2, w, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v(1, 0), 1 + 2 * 5);
}
