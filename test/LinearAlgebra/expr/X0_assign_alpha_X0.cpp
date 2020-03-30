#include "LinearAlgebra/expr/X0_assign_alpha_X0.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(X0_assign_alpha_X1, vector)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  Expr_Selector_Enum selected = assign(v, 3, _vector_0_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 3 * 1);
  EXPECT_EQ(v[1], 3 * 2);
  EXPECT_EQ(v[2], 3 * 3);

  // must also works, however this is our internal stuff
  // user normally do not have to use this form 
  selected = assign(v, 3, _vmt_0_t_<_vector_0_t_>());

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 3 * 3 * 1);
  EXPECT_EQ(v[1], 3 * 3 * 2);
  EXPECT_EQ(v[2], 3 * 3 * 3);
}

TEST(X0_assign_alpha_X1, matrix)
{
  Tiny_Matrix<int, 3, 1> v;
  v(0, 0) = 1;
  v(1, 0) = 2;
  v(2, 0) = 3;

  EXPECT_EQ(v(0, 0), 1);
  EXPECT_EQ(v(1, 0), 2);
  EXPECT_EQ(v(2, 0), 3);

  Expr_Selector_Enum selected = assign(v, 3, _matrix_0_);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v(0, 0), 3 * 1);
  EXPECT_EQ(v(1, 0), 3 * 2);
  EXPECT_EQ(v(2, 0), 3 * 3);
}
