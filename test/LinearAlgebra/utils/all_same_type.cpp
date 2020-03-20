#include "LinearAlgebra/utils/all_same_type.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Is_Complete, basic)
{
  EXPECT_TRUE((All_Same_Type_v<>));
  EXPECT_TRUE((All_Same_Type_v<int>));
  EXPECT_TRUE((All_Same_Type_v<int, int>));
  EXPECT_TRUE((All_Same_Type_v<int, int, int>));
  EXPECT_FALSE((All_Same_Type_v<int, int, float, int>));
}
