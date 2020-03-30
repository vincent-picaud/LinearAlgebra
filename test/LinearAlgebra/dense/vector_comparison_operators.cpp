#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_Comparison_Operators, basic)
{
  Vector<double> V1(5);
  V1 = 1;

  Tiny_Vector<int, 5> V2;
  V2 = 1;

  EXPECT_TRUE(V1 == V2);
  EXPECT_TRUE(V1 <= V2);
  EXPECT_TRUE(V1 >= V2);

  EXPECT_FALSE(V1 != V2);
  EXPECT_FALSE(V1 < V2);
  EXPECT_FALSE(V1 > V2);

  V1[2] = 0;
  EXPECT_TRUE(V1 != V2);
  EXPECT_TRUE(V1 <= V2);
  EXPECT_FALSE(V1 >= V2);

  EXPECT_FALSE(V1 == V2);
  EXPECT_FALSE(V1 < V2);
  EXPECT_FALSE(V1 > V2);
}
