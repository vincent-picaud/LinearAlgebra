#include "LinearAlgebra/expr/X_eq_aX.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

//////////////////////////////////////////////////////////////////
// X0 = α rhs
//////////////////////////////////////////////////////////////////
//

TEST(X0_Eq_AX0, vector_blas)
{
  Vector<float> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  DEBUG_RESET_SELECTED();
  assign(v, _product_, Scalar(3), v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(v[0], 3 * 1);
  EXPECT_EQ(v[1], 3 * 2);
  EXPECT_EQ(v[2], 3 * 3);
}

TEST(X0_Eq_AX0, matrix)
{
  Tiny_Matrix<int, 3, 1> v;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  DEBUG_RESET_SELECTED();
  assign(v, _product_, Scalar(3), v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v(0, 0), 3 * 1);
  EXPECT_EQ(v(1, 0), 3 * 2);
  EXPECT_EQ(v(2, 0), 3 * 3);
}

//////////////////////////////////////////////////////////////////
// X0 = α X1
//////////////////////////////////////////////////////////////////
//
TEST(X0_Eq_AX1, vector)
{
  Tiny_Vector<int, 3> v, w;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, Scalar(3), v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 3 * 1);
  EXPECT_EQ(w[1], 3 * 2);
  EXPECT_EQ(w[2], 3 * 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, Scalar(3), w);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 3 * 3 * 1);
  EXPECT_EQ(w[1], 3 * 3 * 2);
  EXPECT_EQ(w[2], 3 * 3 * 3);
}

TEST(X0_Eq_AX1, matrix)
{
  Tiny_Matrix<int, 3, 1> v, w;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, Scalar(3), v);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  EXPECT_EQ(w(0, 0), 3 * 1);
  EXPECT_EQ(w(1, 0), 3 * 2);
  EXPECT_EQ(w(2, 0), 3 * 3);

  DEBUG_RESET_SELECTED();
  assign(w, _product_, Scalar(3), w);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  EXPECT_EQ(w(0, 0), 3 * 3 * 1);
  EXPECT_EQ(w(1, 0), 3 * 3 * 2);
  EXPECT_EQ(w(2, 0), 3 * 3 * 3);
}

// TEST(X0_Eq_AX1, unary_minus)
// {
//   Vector<double> v(3), w(3);
//   v[0] = 1;
//   v[1] = 2;
//   v[2] = 3;

//   DEBUG_RESET_SELECTED();
//   assign(w, _unary_minus_, w);
//   DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
//                   (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));
// }

TEST(X0_Eq_AX1, double_use_blas)
{
  Vector<double> v(3), w(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  DEBUG_RESET_SELECTED();
  assign(v, _product_, Scalar<double>(2), w);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
                  (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));
}
