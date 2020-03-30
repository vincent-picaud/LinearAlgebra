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

TEST(Vector_Comparison_Operators, scalar_mix)
{
  Tiny_Vector<float, 5> VMT;
  VMT = 1;

  EXPECT_TRUE(1 == VMT);
  EXPECT_TRUE(VMT == 1);
  EXPECT_TRUE(2 != VMT);
  EXPECT_TRUE(VMT != 2);

  VMT[2] = 1.1;

  EXPECT_FALSE(1 == VMT);
  EXPECT_TRUE(1 != VMT);
  EXPECT_TRUE(0 <= VMT);
  EXPECT_TRUE(2 >= VMT);
  EXPECT_TRUE(0 < VMT);
  EXPECT_TRUE(2 > VMT);

  EXPECT_FALSE(VMT == 1);
  EXPECT_TRUE(VMT != 1);
  EXPECT_FALSE(VMT <= 0);
  EXPECT_FALSE(VMT >= 2);
  EXPECT_FALSE(VMT < 0);
  EXPECT_FALSE(VMT > 2);
}
