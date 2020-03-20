#include "LinearAlgebra/dense/vector_are_compatible.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_Are_Compatible, Basic)
{
  Tiny_Vector<double, 3> M1;
  Tiny_Vector<int, 2> M2;
  Vector<float> M3(3);

  EXPECT_TRUE(are_compatible_p(M1));
  EXPECT_TRUE(are_compatible_p(M1, M1));
  EXPECT_FALSE(are_compatible_p(M1, M2, M1));
  EXPECT_TRUE(are_compatible_p(M1, M3, M1));

  // TODO: test view too
  //  EXPECT_TRUE(are_compatible_from_to_p(view_as M1, M3, M1));
}
