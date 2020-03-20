#include "LinearAlgebra/utils/is_complete.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

struct A
{
};
struct B;

TEST(Is_Complete, basic)
{
  EXPECT_TRUE((Is_Complete_v<A>));
  EXPECT_FALSE((Is_Complete_v<B>));
}
