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

  Expr_Selector_Enum selected = assign(w, 3, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 3 * 1);
  EXPECT_EQ(w[1], 3 * 2);
  EXPECT_EQ(w[2], 3 * 3);
}
