#include "LinearAlgebra/utils/enum_class_to_value.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

enum class A_Enum : int
{
  One = 1,
  Two = 2
};

TEST(Crtp, trivial)
{
  A_Enum e = A_Enum::Two;
  
  EXPECT_EQ(enum_class_to_value(e),2);
}
