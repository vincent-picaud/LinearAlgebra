#include "LinearAlgebra/expr/V0_assign_alpha_V0_plus_beta_op_M_V1.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_alpha_V0_plus_beta_op_M_V1, basic)
{
  using T = double;

  Tiny_Matrix<T, 3, 2> M;
  Vector<T> y(3);
  Tiny_Vector<T, 2> x;

  M(0, 0) = 1;
  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;
  M(2, 0) = 1;
  M(2, 1) = 1;

  x[0] = 1;
  x[1] = 2;

  //  Expr_Selector_Enum selected = expr(y, _assign_, 0, _vector_0_, _plus_, 2, _identity_, M, x);
  Expr_Selector_Enum selected = expr(y, _assign_, 2, _identity_, M, x, _plus_, 0, _vector_0_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Blas);

  EXPECT_EQ(y[0], 2 * x[0]);
  EXPECT_EQ(y[1], 2 * x[1]);
  EXPECT_EQ(y[2], 2 * (x[0] + x[1]));
}
