#include "LinearAlgebra/dense/vector_is_same.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

#include "LinearAlgebra/dense/matrix_is_same.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Is_Same, vector)
{
  Vector<int> V1(10);
  Vector<double> V2(10);

  EXPECT_TRUE(is_same(V1, V1));
  EXPECT_FALSE(is_same(V1, V2));

  auto V1_view = create_vector_view(V1, 0, 10);

  EXPECT_TRUE(is_same(V1_view, V1));
  EXPECT_FALSE(is_same(V1_view, V2));

  auto V1_view_2 = create_vector_view(V1, 5, 10);

  EXPECT_FALSE(is_same(V1_view_2, V1));
  EXPECT_FALSE(is_same(V1_view_2, V2));
}

TEST(Is_Same, matrix)
{
  Matrix<int> V1(10, 4);
  Matrix<double> V2(10, 4);

  EXPECT_TRUE(is_same(V1, V1));
  EXPECT_FALSE(is_same(V1, V2));
}
