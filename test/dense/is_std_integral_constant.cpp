#include "LinearAlgebra/dense/is_std_integral_constant.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Is_Std_Integral_Constant, Basic)
{
  EXPECT_FALSE((is_std_integral_constant_v<size_t>));
  EXPECT_TRUE((is_std_integral_constant_v<std::integral_constant<size_t, 3>>));

  EXPECT_TRUE((is_std_integral_constant_size_or_std_size_v<std::integral_constant<size_t, 3>>));
  EXPECT_TRUE((is_std_integral_constant_size_or_std_size_v<size_t>));

  EXPECT_FALSE((is_std_integral_constant_size_or_std_size_v<double>));
  EXPECT_FALSE((is_std_integral_constant_size_or_std_size_v<std::integral_constant<char, '3'>>));
}
