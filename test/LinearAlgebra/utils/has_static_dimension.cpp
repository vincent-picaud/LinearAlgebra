#include "LinearAlgebra/utils/has_static_dimension.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

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

TEST(Has_Static_Dimension, only_works_for_VMT_classes)
{
  EXPECT_FALSE((Has_Static_Dimension_v<int>));
  EXPECT_FALSE((Has_Static_Dimension_v<A>));
  EXPECT_FALSE((Has_Static_Dimension_v<B>));
  EXPECT_FALSE((Has_Static_Dimension_v<C<10>>));

  // EXPECT_FALSE((Has_Static_Dimension_v<A, B, A, B>));
  // EXPECT_TRUE((Has_Static_Dimension_v<B, B, A, C<10>, A>));
}

TEST(Has_Static_Dimension, vector)
{
  Vector<int> V_dyn;
  Tiny_Vector<int, 5> V_static;

  EXPECT_FALSE((Has_Static_Dimension_v<decltype(V_dyn)>));
  EXPECT_TRUE((Has_Static_Dimension_v<decltype(V_static)>));
}

TEST(Has_Static_Dimension, matrix)
{
  EXPECT_FALSE((Has_Static_Dimension_v<Matrix<double>>));
  EXPECT_TRUE((Has_Static_Dimension_v<Tiny_Matrix<int, 4, 5>>));
}

TEST(Has_Static_Dimension, any)
{
  EXPECT_FALSE((Any_Has_Static_Dimension_v<Matrix<double>, A, C<10>>));
  EXPECT_TRUE((Any_Has_Static_Dimension_v<Matrix<double>, Tiny_Matrix<int, 4, 5>, A, C<10>>));
}
