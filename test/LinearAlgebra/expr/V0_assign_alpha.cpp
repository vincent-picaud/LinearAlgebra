#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V_assign_alpha, assign)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  DEBUG_RESET_SELECTED();
  assign(v, Scalar<int>(-1));
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], -1);
  EXPECT_EQ(v[1], -1);
  EXPECT_EQ(v[2], -1);

  v = 1;

  EXPECT_EQ(v[0], +1);
  EXPECT_EQ(v[1], +1);
  EXPECT_EQ(v[2], +1);
}
