#include "LinearAlgebra/lapack/subroutines_dense.hpp"

#include "LinearAlgebra/dense/matrix_fill.hpp"

#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Subroutines_Dense, posv)
{
  using T        = double;
  const size_t n = 5;
  Symmetric_Matrix<T> H(n, n);
  Vector<T> q(n);

  fill_indexed([](auto i, auto j) { return 1 / T(i + j + 1); }, H);
  q = -1;

  auto info = Lapack::posv(H, q);
  EXPECT_EQ(info,0);

  fill_indexed([](auto i, auto j) { return 1 / T(i + j + 1); }, H);
  Vector<T> q_dup(n);
  q_dup = H * q;

  scan([](const auto qi) { EXPECT_FLOAT_EQ(qi, -1); }, q_dup);
}
