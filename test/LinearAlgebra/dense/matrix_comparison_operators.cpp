#include "LinearAlgebra/dense/matrix_comparison_operators.hpp"

#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_Comparison_Operators, basic)
{
  Matrix<double> V1(5, 2);
  V1 = 1;

  Tiny_Matrix<int, 5, 2> V2;
  V2 = 1;

  EXPECT_TRUE(V1 == V2);
  EXPECT_TRUE(V1 <= V2);
  EXPECT_TRUE(V1 >= V2);

  EXPECT_FALSE(V1 != V2);
  EXPECT_FALSE(V1 < V2);
  EXPECT_FALSE(V1 > V2);

  V1(2, 1) = 0;
  EXPECT_TRUE(V1 != V2);
  EXPECT_TRUE(V1 <= V2);
  EXPECT_FALSE(V1 >= V2);

  EXPECT_FALSE(V1 == V2);
  EXPECT_FALSE(V1 < V2);
  EXPECT_FALSE(V1 > V2);
}
