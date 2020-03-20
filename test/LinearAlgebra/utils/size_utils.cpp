#include "LinearAlgebra/utils/size_utils.hpp"

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

//////////////////////////////////////////////////////////////////

TEST(Size_Utils, get_static_size_if_any)
{
  constexpr auto s_1 = get_static_size_if_any(1);
  EXPECT_EQ(s_1, 1);

  constexpr auto s_2 = get_static_size_if_any(1, 2);
  EXPECT_EQ(s_2, 2);

  constexpr auto s_3 = get_static_size_if_any(1, 2, std::integral_constant<size_t, 5>());
  EXPECT_EQ(s_3, 5);
  EXPECT_TRUE(
      (std::is_same_v<
          decltype(get_static_size_if_any(1, 2, std::integral_constant<size_t, 5>())),
          std::integral_constant<size_t, 5>>));  // check that we have an std::integral_constant
}

// check predicate: all_sizes_are_equal_p
TEST(Size_Utils, all_sizes_are_equal_p)
{
  EXPECT_FALSE(all_sizes_are_equal_p(size_t(1), size_t(2)));
  EXPECT_TRUE(all_sizes_are_equal_p(size_t(2), size_t(2)));
  EXPECT_TRUE(all_sizes_are_equal_p(size_t(2), std::integral_constant<size_t, 2>(), size_t(2)));
  EXPECT_FALSE(all_sizes_are_equal_p(size_t(2), std::integral_constant<size_t, 5>(), size_t(2)));
  EXPECT_TRUE(all_sizes_are_equal_p(size_t(2)));
}
