#include "LinearAlgebra/utils/lower_upper_bound.hpp"

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Lower_Upper_Bound, lower_bound)
{
  double data[13] = {1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
  auto X          = create_vector_view(data, 13);

  EXPECT_EQ(lower_bound(X, -1), 0);
  EXPECT_EQ(lower_bound(X, 1), 0);
  EXPECT_EQ(lower_bound(X, 2), 2);
  EXPECT_EQ(lower_bound(X, 3), 3);
  EXPECT_EQ(lower_bound(X, 4), 7);
  EXPECT_EQ(lower_bound(X, 3.5), 7);
  EXPECT_EQ(lower_bound(X, 4.5), 10);
  EXPECT_EQ(lower_bound(X, 6), X.size() - 1);
  EXPECT_EQ(lower_bound(X, 100), X.size());
}

TEST(Lower_Upper_Bound, upper_bound)
{
  double data[13] = {1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
  auto X          = create_vector_view(data, 13);

  EXPECT_EQ(upper_bound(X, -1), 0);
  EXPECT_EQ(upper_bound(X, 1), 2);
  EXPECT_EQ(upper_bound(X, 2), 3);
  EXPECT_EQ(upper_bound(X, 3), 7);
  EXPECT_EQ(upper_bound(X, 4), 10);
  EXPECT_EQ(upper_bound(X, 3.5), 7);
  EXPECT_EQ(upper_bound(X, 4.5), 10);
  EXPECT_EQ(upper_bound(X, 6), X.size());
  EXPECT_EQ(upper_bound(X, 100), X.size());
}

TEST(Lower_Upper_Bound, view_from_bound)
{
  double data[13] = {1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6};
  auto X          = create_vector_view(data, 13);

  auto v1 = create_vector_view(X, lower_bound(X, -1), upper_bound(X, -1));
  EXPECT_EQ(v1.size(), 0);

  auto v2 = create_vector_view(X, lower_bound(X, 1), upper_bound(X, 1));
  EXPECT_EQ(v2.size(), 2);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 1);

  auto v3 = create_vector_view(X, lower_bound(X, 2), upper_bound(X, 2));
  EXPECT_EQ(v3.size(), 1);
  EXPECT_EQ(v3[0], 2);

  auto v4 = create_vector_view(X, lower_bound(X, 3), upper_bound(X, 3));
  EXPECT_EQ(v4.size(), 4);
  EXPECT_EQ(v4[0], 3);
  EXPECT_EQ(v4[1], 3);
  EXPECT_EQ(v4[2], 3);
  EXPECT_EQ(v4[3], 3);

  auto v5 = create_vector_view(X, lower_bound(X, 6), upper_bound(X, 6));
  EXPECT_EQ(v5.size(), 1);
  EXPECT_EQ(v5[0], 6);

  // CAVEAT:
  // auto v6 = create_vector_view(X, lower_bound(X, 7), upper_bound(X, 7));
  // triggers an error as begin = lower_bound(X, 7) = end 
  // EXPECT_EQ(v6.size(), 0);
}
