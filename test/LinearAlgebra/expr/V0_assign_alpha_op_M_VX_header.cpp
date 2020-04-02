#include "LinearAlgebra/expr/V0_assign_alpha_op_M_VX_header.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_alpha_op_M_VX_header, blas_trmv)
{
  Vector<double> V(4);
  Upper_Triangular_Matrix<double> T(4, 4);

  V = 1;
  T = 1;

  assign(V, 2, _identity_, T, _lhs_);
}
