#include "LinearAlgebra/expr_of_the_poor/X_assign_X.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Known_Pattern, axpy)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  Vector<int> w(3);
  w[0] = 0;
  w[1] = 0;
  w[2] = 0;

  expr(w, _assign_, v);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);
}
