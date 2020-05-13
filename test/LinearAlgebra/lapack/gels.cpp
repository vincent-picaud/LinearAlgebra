#include "LinearAlgebra/lapack/lapack.hpp"

#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

// NOT TESTED: transpose |A^t.x-b| TODO,
// (only identity is tested so far)
//
TEST(gels, basic_ls)
{
  Matrix<double> M(10, 3);
  Vector<double> b(10);
  double a0 = 10, a1 = 2, a2 = 3;

  for (size_t i = 0; i < 10; i++)
  {
    M(i, 0) = 1;
    M(i, 1) = i;
    M(i, 2) = i * i;
    b[i]    = a0 + a1 * i + a2 * i * i;
  }

  auto info = Lapack::gels(_identity_, M, b);
  EXPECT_EQ(info, 0);

  // CAVEAT: only the first 3-th b component are relevant
  EXPECT_FLOAT_EQ(b[0], 10);
  EXPECT_FLOAT_EQ(b[1], 2);
  EXPECT_FLOAT_EQ(b[2], 3);
}

TEST(gels, basic_ls_matrix_rhs)
{
  Matrix<double> M(10, 3);
  Matrix<double> b(10, 2);
  double a0 = 10, a1 = 2, a2 = 3;

  for (size_t i = 0; i < 10; i++)
  {
    M(i, 0) = 1;
    M(i, 1) = i;
    M(i, 2) = i * i;
    b(i, 0) = a0 + a1 * i + a2 * i * i;
    b(i, 1) = 2 * b(i, 0);
  }

  auto info = Lapack::gels(_identity_, M, b);
  EXPECT_EQ(info, 0);

  // CAVEAT: only the first 3-th b component are relevant
  EXPECT_FLOAT_EQ(b(0, 0), 10);
  EXPECT_FLOAT_EQ(b(1, 0), 2);
  EXPECT_FLOAT_EQ(b(2, 0), 3);

  EXPECT_FLOAT_EQ(b(0, 1), 2 * 10);
  EXPECT_FLOAT_EQ(b(1, 1), 2 * 2);
  EXPECT_FLOAT_EQ(b(2, 1), 2 * 3);
}
