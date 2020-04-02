#include "LinearAlgebra/expr/V0_assign_alpha_op_M_VX_header.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(expr_V0_assign_alpha_op_M_VX_header, blas_trmv)
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
  Upper_Triangular_Matrix<double> L(4, 4);

  W = 1;
  L = 1;

  selected = assign(W, 2, _identity_, L, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Blas);
  EXPECT_EQ(V, W);
}

TEST(expr_V0_assign_alpha_op_M_VX_header, blas_trsv)
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

  selected = assign(V, 0.5, _identity_, _inverse_, U, _lhs_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 1);
  EXPECT_EQ(V[1], 1);
  EXPECT_EQ(V[2], 1);
  EXPECT_EQ(V[3], 1);
}
