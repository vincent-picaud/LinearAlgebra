#include "LinearAlgebra/expr/M0_assign_M1.hpp"
#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Known_Pattern, copy)
{
  Tiny_Matrix<int, 3, 1> v;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;
  Matrix<double> w(3,1);
  w(0, 0) = 0;
  w(1, 0) = 0;
  w(2, 0) = 0;

  Expr_Selector_Enum selected = expr(w, _assign_, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Generic);

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  EXPECT_EQ(w(0, 0), 1);
  EXPECT_EQ(w(1, 0), 2);
  EXPECT_EQ(w(2, 0), 3);
}
