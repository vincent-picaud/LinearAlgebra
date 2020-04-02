#include "LinearAlgebra/expr/V0_assign_alpha_op_M_VX_header.hpp"

#include "LinearAlgebra/metaexpr/metaexpr.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(metaExpr_V0_assign_alpha_op_M_VX_header, blas_trmv)
{
  Vector<double> V(4);
  Upper_Triangular_Matrix<double> U(4, 4);

  V = 1;
  U = 1;

  auto selected = assign(V, 2, _identity_, U, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 8);
  EXPECT_EQ(V[1], 6);
  EXPECT_EQ(V[2], 4);
  EXPECT_EQ(V[3], 2);

  Vector<double> W(4);
  Lower_Triangular_Matrix<double> L(4, 4);

  W = 1;
  L = 1;

  W = 2 * transpose(L) * W;

  EXPECT_EQ(V, W) << "V:" << std::endl << V << std::endl << "W:" << std::endl << W << std::endl;

  W = 2 * identity(L) * W;
}

TEST(metaExpr_V0_assign_alpha_op_M_VX_header, trmv_check_alias)
{
  Vector<std::complex<double>> V(4);
  Upper_Triangular_Matrix<std::complex<double>> U(4, 4);

  V = 1;
  U = 1;

  V = U * V;
  V = 2 * U * V;
  V = transpose(U) * V;
}
