#include "LinearAlgebra/expr/V_assign_alpha.hpp"

#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V_assign_alpha, assign)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  Expr_Selector_Enum selected = assign(v, -1);
  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], -1);
  EXPECT_EQ(v[1], -1);
  EXPECT_EQ(v[2], -1);

  v = 1;

  EXPECT_EQ(v[0], +1);
  EXPECT_EQ(v[1], +1);
  EXPECT_EQ(v[2], +1);
}
