#include "LinearAlgebra/expr/V0_assign_V1.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Known_Pattern, copy)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  Vector<int> w(3);
  w[0] = 0;
  w[1] = 0;
  w[2] = 0;

  Expr_Selector_Enum selected = expr(w, _assign_, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);

  selected = expr(v, _assign_, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  selected = expr(w, _assign_, w);

  EXPECT_EQ(selected, Expr_Selector_Enum::Generic);
}
