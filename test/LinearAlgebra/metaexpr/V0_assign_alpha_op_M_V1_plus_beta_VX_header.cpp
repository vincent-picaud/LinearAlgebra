#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_VX_header.hpp"

#include "LinearAlgebra/metaexpr/metaexpr.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_alpha_op_M_V1_plus_beta_VX_header, alias)
{
  Vector<double> V(4);
  Matrix<double> U(4, 4);

  EXPECT_TRUE(false);
}
