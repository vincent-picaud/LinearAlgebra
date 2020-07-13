
#include "LinearAlgebra/dense/vector_fwd.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/expr/v_eq_aMv_bv.hpp"

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
  assign(
      y, _plus_, _product_, _product_, Scalar<T>(2), _identity_, M, x, _product_, Scalar<T>(0), y);
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
  assign(
      y, _plus_, _product_, _product_, Scalar<T>(2), _identity_, M, x, _product_, Scalar<T>(0), y);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  // y_cpy_as_int = 2 * transpose(M) * x + 0 * y_cpy_as_int;
  // EXPECT_EQ(y, y_cpy_as_int);
}

// Alias test
//
TEST(v_eq_aMv_bv, alias)
{
  [[maybe_unused]] double alpha = 1 / 10.;
  [[maybe_unused]] double beta  = 2 / 10.;
  [[maybe_unused]] double gamma = 3 / 10.;

  [[maybe_unused]] Tiny_Vector<double, 1> v0, v1, v2;
  v0 = 1 / 100.;
  v1 = 2 / 100.;
  v2 = 3 / 100.;

  [[maybe_unused]] Tiny_Matrix<double, 1, 1> M0, M1, M2;
  M0 = 1 / 1000.;
  M1 = 2 / 1000.;
  M2 = 3 / 1000.;

  v0 = M1 * v1 + beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.002000) * (0.020000)) + ((0.200000) * (0.030000)));

  v0 = M1 * v1 - v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.002000) * (0.020000)) - (0.030000));

  v0 = v2 + alpha * M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) + (((0.100000) * (0.002000)) * (0.020000)));

  v0 = v2 + alpha * transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) + (((0.100000) * (0.002000)) * (0.020000)));

  v0 = v2 - M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) - ((0.002000) * (0.020000)));

  v0 = v2 - transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) - ((0.002000) * (0.020000)));

  v0 = v2 - alpha * M1 * v1; // X
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) - (((0.100000) * (0.002000)) * (0.020000)));

  v0 = transpose(M1) * v1 + v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.002000) * (0.020000)) + (0.030000));

  v0 = transpose(M1) * v1 + beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.002000) * (0.020000)) + ((0.200000) * (0.030000)));

  v0 = transpose(M1) * v1 - v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.002000) * (0.020000)) - (0.030000));

  v0 = alpha * M1 * v1 + beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(),
                   (((0.100000) * (0.002000)) * (0.020000)) + ((0.200000) * (0.030000)));

  v0 = alpha * M1 * v1 - beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(),
                   (((0.100000) * (0.002000)) * (0.020000)) - ((0.200000) * (0.030000)));

  v0 = alpha * M1 * v1 + v2;
  EXPECT_DOUBLE_EQ(*v0.data(), (((0.100000) * (0.002000)) * (0.020000)) + (0.030000));

  v0 = alpha * M1 * v1 - v2;
  EXPECT_DOUBLE_EQ(*v0.data(), (((0.100000) * (0.002000)) * (0.020000)) - (0.030000));

  v0 = alpha * transpose(M1) * v1 + v2;
  EXPECT_DOUBLE_EQ(*v0.data(), (((0.100000) * (0.002000)) * (0.020000)) + (0.030000));

  v0 = alpha * transpose(M1) * v1 - v2;
  EXPECT_DOUBLE_EQ(*v0.data(), (((0.100000) * (0.002000)) * (0.020000)) - (0.030000));

  v0 = alpha * transpose(M1) * v1 + beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(),
                   (((0.100000) * (0.002000)) * (0.020000)) + ((0.200000) * (0.030000)));

  v0 = beta * v2 + alpha * M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(),
                   ((0.200000) * (0.030000)) + (((0.100000) * (0.002000)) * (0.020000)));

  v0 = beta * v2 - alpha * M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(),
                   ((0.200000) * (0.030000)) - (((0.100000) * (0.002000)) * (0.020000)));

  v0 = beta * v2 + M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.200000) * (0.030000)) + ((0.002000) * (0.020000)));

  v0 = beta * v2 + transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.200000) * (0.030000)) + ((0.002000) * (0.020000)));

  v0 = beta * v2 + alpha * transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), // 
                   ((0.200000) * (0.030000)) + (((0.100000) * (0.002000)) * (0.020000)));

  v0 = beta * v2 - M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.200000) * (0.030000)) - ((0.002000) * (0.020000)));

  v0 = beta * v2 - transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.200000) * (0.030000)) - ((0.002000) * (0.020000)));

  v0 = beta * v2 - alpha * transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(),
                   ((0.200000) * (0.030000)) - (((0.100000) * (0.002000)) * (0.020000)));

  v0 = -M1 * v1 + v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((-(0.002000)) * (0.020000)) + (0.030000));

  v0 = -M1 * v1 + beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((-(0.002000)) * (0.020000)) + ((0.200000) * (0.030000)));

  v0 = -M1 * v1 - v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((-(0.002000)) * (0.020000)) - (0.030000));

  v0 = -v2 + M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(0.030000)) + ((0.002000) * (0.020000)));

  v0 = -v2 + transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(0.030000)) + ((0.002000) * (0.020000)));

  v0 = -v2 + alpha * M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(0.030000)) + (((0.100000) * (0.002000)) * (0.020000)));

  v0 = -v2 + alpha * transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(0.030000)) + (((0.100000) * (0.002000)) * (0.020000)));

  v0 = -v2 - M1 * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(0.030000)) - ((0.002000) * (0.020000)));

  v0 = -v2 - transpose(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(0.030000)) - ((0.002000) * (0.020000)));

  v0 = -transpose(M1) * v1 + v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((-(0.002000)) * (0.020000)) + (0.030000));

  v0 = -transpose(M1) * v1 + beta * v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((-(0.002000)) * (0.020000)) + ((0.200000) * (0.030000)));

  v0 = -transpose(M1) * v1 - v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((-(0.002000)) * (0.020000)) - (0.030000));
}
