
#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"
#include "LinearAlgebra/expr/M_eq_aMM_bM_matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Syrk, Gemm)
{
  Matrix<double> A(2, 3);

  A(0, 0) = 0;
  A(1, 0) = 1;
  A(0, 1) = -4;
  A(1, 1) = 3;
  A(0, 2) = 2;
  A(1, 2) = -4;

  // Precomputed AtA & AAt
  //
  Matrix<double> AAt(2, 2);

  AAt(0, 0) = 20;
  AAt(1, 0) = -20;

  AAt(0, 1) = -20;
  AAt(1, 1) = 26;

  Matrix<double> AtA(3, 3);

  AtA(0, 0) = 1;
  AtA(1, 0) = 3;
  AtA(2, 0) = -4;

  AtA(0, 1) = 3;
  AtA(1, 1) = 25;
  AtA(2, 1) = -20;

  AtA(0, 2) = -4;
  AtA(1, 2) = -20;
  AtA(2, 2) = 20;

  Symmetric_Matrix<double> C_AAt(2, 2), C_AtA(3, 3);
  C_AAt = 1;
  C_AtA = 1;

  C_AAt = 2 * identity(A) * transpose(A) + 3 * C_AAt;
  // C_AtA = 2 * transpose(A) * identity(A) + 3 * C_AtA;

  // EXPECT_EQ(C_AAt(0, 0), AAt(0, 0));
  // EXPECT_EQ(C_AAt(1, 0), AAt(1, 0));
  // EXPECT_EQ(C_AAt(2, 0), AAt(2, 0));

  // Matrix<double> Full_C_AAt(2, 2), Full_C_AtA(3, 3);

  // Full_C_AAt = 1;
  // Full_C_AtA = 1;

  // Full_C_AAt = 2 * identity(A) * transpose(A) + 3 * Full_C_AAt;
  // Full_C_AtA = 2 * transpose(A) * identity(A) + 3 * Full_C_AtA;
}
