#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/expr/vector_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Tiny_Vector_View, Constructor)
{
  Tiny_Vector<int, 10> v;
  expr(v, _assign_, 1);
  auto view_v = view(v, 1, 3);
  expr(view_v, _assign_, 2);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 1);
}
