#include "LinearAlgebra/expr_of_the_poor/dimension.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Dimension, dimension)
{
  Tiny_Matrix<int, 3, 2> M;
  auto M_dim = dimension_predicate(M);

  EXPECT_EQ(M_dim.I_size(), 3);
  EXPECT_EQ(M_dim.J_size(), 2);

  EXPECT_FALSE(M_dim * M_dim);

  auto Mt_dim = matrix_op(_transConj_, M_dim);

  EXPECT_EQ(Mt_dim.I_size(), 2);
  EXPECT_EQ(Mt_dim.J_size(), 3);

}
