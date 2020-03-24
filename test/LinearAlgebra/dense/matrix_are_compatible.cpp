#include "LinearAlgebra/dense/matrix_are_compatible.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_view.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_Are_Compatible, Basic)
{
  Tiny_Matrix<double, 3, 2> M1;
  Tiny_Matrix<int, 3, 2> M2;
  Tiny_Matrix<float, 2, 3> M3;

  EXPECT_TRUE(are_compatible_p(M1));
  EXPECT_TRUE(are_compatible_p(M1, M1));
  EXPECT_TRUE(are_compatible_p(M1, M2, M1));
  EXPECT_FALSE(are_compatible_p(M1, M3, M1));
  EXPECT_FALSE(are_compatible_p(M1, M3, M1));

  Tiny_Unit_Lower_Triangular_Matrix<int, 3, 5> M5;
  Matrix<double> M6(3, 5);

  EXPECT_FALSE(are_compatible_p(M5, M6));
  EXPECT_TRUE(are_compatible_p(M5, create_matrix_view_strict_lower_triangular(M6)));
}
