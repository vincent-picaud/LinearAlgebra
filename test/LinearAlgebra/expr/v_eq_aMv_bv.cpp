#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(v_eq_aMv_bv, blas_gemv)
{
  using T = double;

  Tiny_Matrix<T, 3, 2> M;
  Vector<T> y(3);
  Tiny_Vector<T, 2> x;

  M(0, 0) = 1;
  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;
  M(2, 0) = 1;
  M(2, 1) = 1;

  x[0] = 1;
  x[1] = 2;

  DEBUG_RESET_SELECTED();
  assign(y,
         _plus_,
         _product_,
         _product_,
         Scalar<T>(2),
         _identity_,
         M,
         x,
         _product_,
         Scalar<T>(0),
         y);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(y[0], 2 * x[0]);
  EXPECT_EQ(y[1], 2 * x[1]);
  EXPECT_EQ(y[2], 2 * (x[0] + x[1]));
}

TEST(v_eq_aMv_bv, blas_symv)
{
  using T = double;

  Tiny_Symmetric_Matrix<T, 3> M;
  Vector<T> y(3);
  Tiny_Vector<T, 3> x;

  M(0, 0) = 1;
  //  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;

  M(2, 0) = 1;
  M(2, 1) = 1;
  M(2, 2) = 1;

  x[0] = 1;
  x[1] = 2;

  auto y_cpy_as_int = similar(Type_v<int>, y);

  DEBUG_RESET_SELECTED();
  assign(y,
         _plus_,
         _product_,
         _product_,
         Scalar<T>(2),
         _identity_,
         M,
         x,
         _product_,
         Scalar<T>(0),
         y);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  // y_cpy_as_int = 2 * transpose(M) * x + 0 * y_cpy_as_int;
  // EXPECT_EQ(y, y_cpy_as_int);
}