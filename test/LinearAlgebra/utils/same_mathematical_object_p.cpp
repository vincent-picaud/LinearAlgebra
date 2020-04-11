#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Same_Mathematical_Object_P, vector)
{
  Vector<int> V1(10);
  Vector<double> V2(10);

  EXPECT_TRUE(same_mathematical_object_p(V1, V1));
  EXPECT_FALSE(same_mathematical_object_p(V1, V2));

  auto V1_view = create_vector_view(V1, 0, 10);

  EXPECT_TRUE(same_mathematical_object_p(V1_view, V1));
  EXPECT_FALSE(same_mathematical_object_p(V1_view, V2));

  auto V1_view_2 = create_vector_view(V1, 5, 10);

  EXPECT_FALSE(same_mathematical_object_p(V1_view_2, V1));
  EXPECT_FALSE(same_mathematical_object_p(V1_view_2, V2));
}

TEST(Same_Mathematical_Object_P, matrix)
{
  Matrix<int> V1(10, 4);
  Matrix<double> V2(10, 4);

  EXPECT_TRUE(same_mathematical_object_p(V1, V1));
  EXPECT_FALSE(same_mathematical_object_p(V1, V2));
}

TEST(Same_Mathematical_Object_P, matrix_vector)
{
  Matrix<int> M1(10, 4);
  Vector<int> V1(10);

  EXPECT_FALSE(same_mathematical_object_p(M1, V1));
}
