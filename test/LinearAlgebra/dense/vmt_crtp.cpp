#include "LinearAlgebra/dense/lhs.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(VMT_Crtp, LHS)
{
  Vector<int> V0(4), V1(4), V2(4);
  Matrix<int> M1(4, 4);
  //  V0 = V1 + LHS();
  //  V0 = 4 * LHS();
  // V0 = M1 * LHS();
}
