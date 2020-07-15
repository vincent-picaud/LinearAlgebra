#include "LinearAlgebra/dense/vector_fwd.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include "LinearAlgebra/expr/X0_eq_aX1_X2.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(X0_eq_aX1_X2, alias_vector) // no need to check matrix (same
				 // routines)
{
  [[maybe_unused]] double alpha = 1 / 10.;
  [[maybe_unused]] double beta  = 2 / 10.;
  [[maybe_unused]] double gamma = 3 / 10.;

  [[maybe_unused]] Tiny_Vector<double, 1> v0, v1, v2;
  v0 = 1 / 100.;
  v1 = 2 / 100.;
  v2 = 3 / 100.;

  [[maybe_unused]] Tiny_Lower_Triangular_Matrix<double, 1, 1> M0, M1, M2;
  M0 = 1 / 1000.;
  M1 = 2 / 1000.;
  M2 = 3 / 1000.;

  v0 = alpha * v1 + v2;
  EXPECT_DOUBLE_EQ(*v0.data(), ((0.100000) * (0.020000)) + (0.030000));

  v0 = v2 + alpha * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) + ((0.100000) * (0.020000)));

  v0 = v2 - alpha * v1;
  EXPECT_DOUBLE_EQ(*v0.data(), (0.030000) - ((0.100000) * (0.020000)));
}
