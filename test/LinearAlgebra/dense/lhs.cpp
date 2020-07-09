#include "LinearAlgebra/dense/lhs.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(VMT_Crtp, LHS)
{
  Vector<int> V0(4), V1(4), V2(4);
  Matrix<int> M0(4, 4), M1(4, 4);
  //  V0 = V1 + LHS();
  //  V0 = 4 * lhs(V0);
  M0 = M1 * lhs(M0);
}
