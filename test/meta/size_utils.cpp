#include "LinearAlgebra/meta/size_utils.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

struct A
{
};
struct B
{
  using size_type = std::size_t;
};
template <std::size_t N>
struct C
{
  using size_type = std::integral_constant<std::size_t, N>;
};

TEST(Size_Utils, Has_Static_Size)
{
  EXPECT_FALSE((Has_Static_Size_v<A>));
  EXPECT_FALSE((Has_Static_Size_v<B>));
  EXPECT_TRUE((Has_Static_Size_v<C<10>>));
}
TEST(Size_Utils, Any_Has_Static_Size)
{
  EXPECT_FALSE((Any_Has_Static_Size_v<A>));
  EXPECT_FALSE((Any_Has_Static_Size_v<B>));
  EXPECT_TRUE((Any_Has_Static_Size_v<C<10>>));

  EXPECT_FALSE((Any_Has_Static_Size_v<A, B, A, B>));
  EXPECT_TRUE((Any_Has_Static_Size_v<B, B, A, C<10>, A>));
}
