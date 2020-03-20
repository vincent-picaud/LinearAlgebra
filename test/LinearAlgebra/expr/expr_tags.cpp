#include "LinearAlgebra/expr/expr_tags.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Expr_Tags, matrix_op)
{
  EXPECT_EQ(_identity_, conjugate(_conjugate_));
  EXPECT_EQ(_transConj_, transpose(_conjugate_));
  EXPECT_EQ(_transConj_, conjugate(_transpose_));

  EXPECT_TRUE(does_it_transpose_matrix_dimension(_transpose_));
  EXPECT_FALSE(does_it_transpose_matrix_dimension(_conjugate_));
}
