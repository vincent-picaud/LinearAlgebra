#include "LinearAlgebra/dense/vector_transform.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_Transform, basic)
{
  Tiny_Vector<int, 3> v;

  EXPECT_EQ(v.size(), 3);

  v[0] = 0;
  v[1] = 1;
  v[2] = 2;

  transform(v, [](const auto v_i) { return v_i + 1; });

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  transform_indexed(v, [](const auto v_i, const std::size_t i) { return v_i + i; });

  EXPECT_EQ(v[0], 1 + 0);
  EXPECT_EQ(v[1], 2 + 1);
  EXPECT_EQ(v[2], 3 + 2);
}
