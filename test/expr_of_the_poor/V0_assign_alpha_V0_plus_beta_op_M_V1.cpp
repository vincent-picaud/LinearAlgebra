#include "LinearAlgebra/expr_of_the_poor/V0_assign_alpha_V0_plus_beta_op_M_V1.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Known_Pattern, copy)
{
  using T = double;

  
  Tiny_Matrix<T, 3, 2> M;
  Vector<T> y(3);
  Tiny_Vector<T, 2> x;

  Expr_Selector_Enum selected = expr(y, _assign_, 1, _vector_0_, _plus_, 2, _identity_, M, x);

  EXPECT_EQ(selected, Expr_Selector_Enum::Blas);
}
