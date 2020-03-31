#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(MetaExpr_Crtp, basic_1)
{
  const size_t n = 4;
  int data[n]    = {1, 2, 3, 4};

  auto V1 = create_vector_view(data, n);

  Vector<double> V2(n);
  V2 = 2;

  V2 = V2 + 4 * V1;

  EXPECT_EQ(V2[0], 2 + 4 * V1[0]);
  EXPECT_EQ(V2[1], 2 + 4 * V1[1]);

  Vector<double> V3(n);
  V3 = 2;

  // V3 = 4 * V1 + V3;

  // EXPECT_EQ(V2,V3);

  EXPECT_EQ(V2, V1);
}
