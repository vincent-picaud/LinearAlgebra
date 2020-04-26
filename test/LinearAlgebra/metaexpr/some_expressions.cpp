#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V2_driver.hpp"

#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(MetaExpr_Crtp, vector_basic_1)
{
  const size_t n = 4;
  int data[n]    = {1, 2, 3, 4};

  auto X1 = create_vector_view(data, n);

  Vector<double> X2(n);
  X2 = 2;

  auto X2_cpy = X2;

  X2 = X2 + 4 * X1;

  EXPECT_EQ(X2[0], X2_cpy[0] + 4 * X1[0]);
  EXPECT_EQ(X2[2], X2_cpy[2] + 4 * X1[2]);
}

TEST(MetaExpr_Crtp, matrix_basic_1)
{
  const size_t n = 4;
  int data[n]    = {1, 2, 3, 4};

  auto X1 = create_matrix_view(data, n, 1);

  Matrix<double> X2(n, 1);
  X2 = 2;

  auto X2_cpy = X2;

  //  X2 = X2 + 4 * X1;
  X2 = 4 * X1 + X2;

  EXPECT_EQ(X2(0, 0), X2_cpy(0, 0) + 4 * X1(0, 0));
  EXPECT_EQ(X2(2, 0), X2_cpy(2, 0) + 4 * X1(2, 0));
}

TEST(MetaExpr_Crtp, gemv)
{
  const size_t n = 5, m = 2;
  Matrix<double> M(n, m);
  Vector<double> x(m), y(n);
  M = 1;
  x = 2;
  y = 3;
  // TODO
  assign(y,
         _plus_,
         _product_,
         _product_,
         Scalar_CRef<double>(4),
         M,
         x,
         _product_,
         Scalar_CRef<double>(2),
         y);

  y = 4 * M * x + 2 * y;
  y = 4 * M * x - 2 * y;
  y = 2 * y + 4 * M * x;
  y = 2 * y - 4 * M * x;

  EXPECT_DEBUG_DEATH((y = 2 * y + 4 * transpose(M) * x), "");  // bad dimension

  //  y = 1 * conjugate(M) * x + 1 * y;

  // y = transpose(M);
}

TEST(MetaExpr_Crtp, symv)
{
  using T        = float;
  const size_t n = 5;
  Symmetric_Matrix<T> M(n, n);
  Vector<T> x(n), y(n);

  x = 1;
  y = 2;
  M = 3;

  y = M * x + 2 * x;
}
