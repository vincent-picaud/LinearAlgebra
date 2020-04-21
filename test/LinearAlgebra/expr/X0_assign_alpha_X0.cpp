#include "LinearAlgebra/expr/X_eq_aX_matrix.hpp"
#include "LinearAlgebra/expr/X_eq_aX_vector.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(X0_Assign_Alpha_X0, vector)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  DEBUG_RESET_SELECTED();
  assign(v, _product_, Scalar_CRef(3), _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 3 * 1);
  EXPECT_EQ(v[1], 3 * 2);
  EXPECT_EQ(v[2], 3 * 3);
}

TEST(X0_Assign_Alpha_X0, matrix)
{
  Tiny_Matrix<int, 3, 1> v;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  DEBUG_RESET_SELECTED();
  assign(v, _product_, Scalar_CRef(3), _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(v(0, 0), 3 * 1);
  EXPECT_EQ(v(1, 0), 3 * 2);
  EXPECT_EQ(v(2, 0), 3 * 3);
}
