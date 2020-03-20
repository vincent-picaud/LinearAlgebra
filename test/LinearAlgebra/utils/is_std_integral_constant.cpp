#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Is_Std_Integral_Constant, Basic)
{
  EXPECT_FALSE((Is_Std_Integral_Constant_v<size_t>));
  EXPECT_TRUE((Is_Std_Integral_Constant_v<std::integral_constant<size_t, 3>>));

  EXPECT_TRUE((Is_Std_Integral_Constant_Size_Or_Std_Size_v<std::integral_constant<size_t, 3>>));
  EXPECT_TRUE((Is_Std_Integral_Constant_Size_Or_Std_Size_v<size_t>));

  EXPECT_FALSE((Is_Std_Integral_Constant_Size_Or_Std_Size_v<double>));
  EXPECT_FALSE((Is_Std_Integral_Constant_Size_Or_Std_Size_v<std::integral_constant<char, '3'>>));
}
