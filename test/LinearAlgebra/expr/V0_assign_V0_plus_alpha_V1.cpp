#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/expr/vector_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_V0_plus_alpha_V1, generic)
{
  Tiny_Vector<int, 3> v;
  Vector<int> w(3);

  iota(v, 1);
  iota(w, 5);

  Expr_Selector_Enum selected = expr(v, _assign_, _vector_0_, _plus_, 2, w);

  EXPECT_TRUE(selected == Expr_Selector_Enum::Generic);
  EXPECT_EQ(v[0], 1 + 2 * w[0]);
  EXPECT_EQ(v[1], 2 + 2 * w[1]);
  EXPECT_EQ(v[2], 3 + 2 * w[2]);
}
