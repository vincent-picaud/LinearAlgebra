#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(M0_assign_alpha_M0_plus_beta_V0_op_V0, Generic)
{
  Tiny_Vector<int, 3> v;
  Symmetric_Matrix<float> S(3, 3);

  iota(v, 1);

  expr(S, _assign_, 0, _matrix_0_, _plus_, 2, v, _transpose_, _vector_0_);

  EXPECT_EQ(S(0, 0), 2);
  EXPECT_EQ(S(1, 0), 4);
  EXPECT_EQ(S(2, 0), 6);

  EXPECT_EQ(S(1, 1), 8);
  EXPECT_EQ(S(2, 1), 12);

  EXPECT_EQ(S(2, 2), 18);
}
