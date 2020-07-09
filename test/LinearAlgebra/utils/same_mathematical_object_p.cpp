#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

#include "LinearAlgebra/dense/lhs.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Same_Mathematical_Object_P, vector)
{
  Vector<int> V1(10);
  Vector<double> V2(10);

  EXPECT_TRUE(same_mathematical_object_p(V1, V1));
  EXPECT_FALSE(same_mathematical_object_p(V1, V2));

  auto V1_view = create_vector_view(V1, 0, 10);

  // CAVEAT: We simplified our =same_mathematical_object_p= routine
  // and now V and its view are *not longer* the same object.
  //
  EXPECT_FALSE(same_mathematical_object_p(V1_view, V1));
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

// With LHS
//
TEST(Same_Mathematical_Object_P, vector_lhs)
{
  Vector<int> V1(4), V2(4);
  auto LHS_V1 = lhs(V1);
  auto LHS_V2 = lhs(V2);

  EXPECT_TRUE(same_mathematical_object_p(V1, LHS_V1));
  EXPECT_FALSE(same_mathematical_object_p(V2, LHS_V1));
  EXPECT_TRUE(same_mathematical_object_p(LHS_V1, V1));
  EXPECT_TRUE(same_mathematical_object_p(LHS_V1, LHS_V1));
  EXPECT_FALSE(same_mathematical_object_p(LHS_V1, LHS_V2));
}

TEST(Same_Mathematical_Object_P, matrix_lhs)
{
  Matrix<int> M1(10, 4), M2(10, 4);
  auto LHS_M1 = lhs(M1);
  auto LHS_M2 = lhs(M2);

  EXPECT_TRUE(same_mathematical_object_p(M1, LHS_M1));
  EXPECT_FALSE(same_mathematical_object_p(M2, LHS_M1));
  EXPECT_TRUE(same_mathematical_object_p(LHS_M1, M1));
  EXPECT_TRUE(same_mathematical_object_p(LHS_M1, LHS_M1));
  EXPECT_FALSE(same_mathematical_object_p(LHS_M1, LHS_M2));
}
