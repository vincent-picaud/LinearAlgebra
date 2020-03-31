//#include "LinearAlgebra/expr/V0_assign_V1_plus_alpha_V2.hpp"
#include "LinearAlgebra/expr/X0_assign_X0_plus_alpha_X1.hpp"

#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_V0_plus_alpha_V1, generic)
{
  Tiny_Vector<int, 3> v;
  Vector<int> w(3);

  iota(v, 1);
  iota(w, 5);

  Expr_Selector_Enum selected = assign(v, _lhs_, _plus_, 2, w);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);
  EXPECT_EQ(v[0], 1 + 2 * w[0]);
  EXPECT_EQ(v[1], 2 + 2 * w[1]);
  EXPECT_EQ(v[2], 3 + 2 * w[2]);
}

TEST(V0_assign_V0_plus_alpha_V1, generic_alias)
{
  Tiny_Vector<int, 3> v;
  Vector<int> w(3);

  iota(v, 1);
  iota(w, 5);

  Expr_Selector_Enum selected = assign(v, 2, w, _plus_, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);
  EXPECT_EQ(v[0], 1 + 2 * w[0]);
  EXPECT_EQ(v[1], 2 + 2 * w[1]);
  EXPECT_EQ(v[2], 3 + 2 * w[2]);
}

// TEST(V0_assign_V0_plus_alpha_V1, generic)
// {
//   Tiny_Vector<int, 3> v;
//   Vector<int> w(3);

//   iota(v, 1);
//   iota(w, 5);

//   Expr_Selector_Enum selected = assign(v, v, _plus_, 2, w);

//   EXPECT_TRUE(selected == Expr_Selector_Enum::Generic);
//   EXPECT_EQ(v[0], 1 + 2 * w[0]);
//   EXPECT_EQ(v[1], 2 + 2 * w[1]);
//   EXPECT_EQ(v[2], 3 + 2 * w[2]);
// }
