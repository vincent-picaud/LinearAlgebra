#include "LinearAlgebra/hello.hpp"
#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Hello, demo)
{
  ASSERT_EQ(hello(),"Hello LinearAlgebra");
}
