#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_Crtp_Size_Utils, get_size)
{
  // Tiny_Vector<int, 4> tv;
  // Vector<float> v(5);

  // EXPECT_EQ(get_size(tv, v), 4);
  // EXPECT_EQ(get_size(tv, tv), 4);
  // EXPECT_EQ(get_size(v, v), 5);

  // auto tv_size = get_size(v, v, v, tv, tv, v, v);

  // EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 4>, decltype(tv_size)>));

  // auto v_size = get_size(v, v, v, v, v, v, v);

  // EXPECT_TRUE((std::is_same_v<std::size_t, decltype(v_size)>));
  // EXPECT_EQ(v_size, 5);
}
