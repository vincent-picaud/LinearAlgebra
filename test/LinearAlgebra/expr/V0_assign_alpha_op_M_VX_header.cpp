#include "LinearAlgebra/expr/V0_assign_alpha_op_M_VX_header.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_fwd.hpp"
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

  DEBUG_RESET_SELECTED();
  assign(V, _product_, _product_, Scalar_CRef<double>(2), _identity_, U, _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 8);
  EXPECT_EQ(V[1], 6);
  EXPECT_EQ(V[2], 4);
  EXPECT_EQ(V[3], 2);

  Vector<double> W(4);
  Upper_Triangular_Matrix<double> L(4, 4);

  W = 1;
  L = 1;

  DEBUG_RESET_SELECTED();
  assign(W, _product_, _product_, Scalar_CRef<double>(2), _identity_, L, _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(V, W);
}

TEST(expr_V0_assign_alpha_op_M_VX_header, blas_trsv)
{
  Vector<double> V(4);
  Upper_Triangular_Matrix<double> U(4, 4);

  V = 1;
  U = 1;

  DEBUG_RESET_SELECTED();
  assign(V, _product_, _product_, Scalar_CRef<double>(2), _identity_, U, _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 8);
  EXPECT_EQ(V[1], 6);
  EXPECT_EQ(V[2], 4);
  EXPECT_EQ(V[3], 2);

  DEBUG_RESET_SELECTED();
  assign(V, _product_, _product_, Scalar_CRef<double>(0.5), _identity_, _inverse_, U, _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 1);
  EXPECT_EQ(V[1], 1);
  EXPECT_EQ(V[2], 1);
  EXPECT_EQ(V[3], 1);
}

//
// For these functions, gemv, symv, etc... for the moment only
//
// assign(V, _product_, _product_, Scalar_CRef<double>(2), _identity_, U, W);
//
// is implemented... the version with _lhs_ is not yet implemented
//
// assign(V, _product_, _product_, Scalar_CRef<double>(2), _identity_, U, _lhs_);
//
// HOWEVER: I do not think one must implement it (as it does not
//          happens in expression template)
//
TEST(expr_V0_assign_alpha_op_M_VX_header, blas_gemv)
{
  Vector<double> V(4), W(4);
  Matrix<double> U(4, 4);

  V       = 1;
  W       = 1;
  U       = 1;
  U(3, 0) = 2;

  DEBUG_RESET_SELECTED();
  assign(V, _product_, _product_, Scalar_CRef<double>(2), _identity_, U, W);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 8);
  EXPECT_EQ(V[1], 8);
  EXPECT_EQ(V[2], 8);
  EXPECT_EQ(V[3], 10);
}

TEST(expr_V0_assign_alpha_op_M_VX_header, blas_symv)
{
  Vector<double> V(4), W(4);
  Symmetric_Matrix<double> U(4, 4);

  V       = 1;
  W       = 1;
  U       = 1;
  U(3, 0) = 2;

  DEBUG_RESET_SELECTED();
  assign(V, _product_, _product_, Scalar_CRef<double>(2), _identity_, U, W);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(V[0], 10);
  EXPECT_EQ(V[1], 8);
  EXPECT_EQ(V[2], 8);
  EXPECT_EQ(V[3], 10);
}
