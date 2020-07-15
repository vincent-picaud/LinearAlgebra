#include "LinearAlgebra/dense/vector_fwd.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/expr/v_eq_a_inv_Mv_bv.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(v_eq_a_inv_Mv_bv, alias)
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

  v0 = alpha * inverse(op1(M1)) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.100000) * (1. / (0.002000))) * (0.020000));

  v0 = -inverse(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(1. / (0.002000))) * (0.020000));

  v0 = -inverse(op1(M1)) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (-(1. / (0.002000))) * (0.020000));

  v0 = inverse(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (1. / (0.002000)) * (0.020000));

  v0 = alpha * inverse(M1) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.100000) * (1. / (0.002000))) * (0.020000));

  v0 = inverse(op1(M1)) * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (1. / (0.002000)) * (0.020000));
}
