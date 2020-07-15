#include "LinearAlgebra/expr/X_eq_neg_X.hpp"

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(X_eq_neg_X, vector)
{
  Tiny_Vector<double, 2> V,W;
  V = 1;

  assign(W, _unary_minus_, V);

  EXPECT_EQ(W[0], -V[0]);
  EXPECT_EQ(W[1], -V[1]);
}
