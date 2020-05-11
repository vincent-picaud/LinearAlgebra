#include "LinearAlgebra/scalar_functions/min_max_vector.hpp"
//
// keep include split apart to check them!
//
#include "LinearAlgebra/vector.hpp"
//
#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(min_max, empty_vector)
{
  Tiny_Vector<int, 0> v;

  EXPECT_EQ(min(v), std::numeric_limits<int>::max());
  EXPECT_EQ(max(v), std::numeric_limits<int>::min());
}

TEST(min_max, basic_vector)
{
  auto v_1 = create_vector({1, 2, 3});
  auto v_2 = create_vector({3, 2, 1});

  EXPECT_EQ(min(v_1), 1);
  EXPECT_EQ(max(v_1), 3);

  EXPECT_EQ(min(v_2), 1);
  EXPECT_EQ(max(v_2), 3);
}
