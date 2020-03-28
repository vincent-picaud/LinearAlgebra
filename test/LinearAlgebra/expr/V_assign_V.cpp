#include "LinearAlgebra/expr/V_assign_V.hpp"

#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V_assign_V, copy)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  Vector<int> w(3);
  w[0] = 0;
  w[1] = 0;
  w[2] = 0;

  Expr_Selector_Enum selected = expr(w, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);
}

TEST(V_assign_V, copy_assert)
{
  Tiny_Vector<int, 3> v;
  EXPECT_DEBUG_DEATH(expr(v, v),"");
}

TEST(V_assign_V, copy_assert_2)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<int, 2> w;
  EXPECT_DEBUG_DEATH(expr(v, w),"");
}
