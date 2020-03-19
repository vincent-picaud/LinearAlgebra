#include "LinearAlgebra/dense/vector_map.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_Map, basic)
{
  Tiny_Vector<int, 3> v;

  EXPECT_EQ(v.size(), 3);

  v[0] = 0;
  v[1] = 1;
  v[2] = 2;

  auto w = map([](const auto v_i) { return (double)v_i + 1; }, v);

  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 2);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);

  EXPECT_EQ(w.size(), 3);
  EXPECT_TRUE(
      (std::is_same_v<typename decltype(w)::size_type, std::integral_constant<std::size_t, 3>>));
  EXPECT_TRUE((std::is_same_v<typename decltype(v)::element_type, int>));
  EXPECT_TRUE((std::is_same_v<typename decltype(w)::element_type, double>));
}
