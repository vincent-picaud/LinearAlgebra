#include "LinearAlgebra/expr/M_eq_aMM_bM_matrix.hpp"

// #include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
// #include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;
TEST(M_aMM_bM, Gemm_with_lhs)
{
  Matrix<double> M(5, 5);

  // assign(M, _plus_, _product_, _product_, 1, _identity_, M, _transpose_, M, _product_, 2, _lhs_);
}

TEST(M_aMM_bM, Symmetric_rank_1)
{
  Symmetric_Matrix<double> symM(5, 5);
  Matrix<double> M(5, 5);

  assign(symM, _plus_, _product_, _product_, 1, _identity_, M, _transpose_, _rhs_1_, _product_, 2,
         _lhs_);
}
