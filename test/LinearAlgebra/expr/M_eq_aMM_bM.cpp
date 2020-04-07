#include "LinearAlgebra/expr/M_eq_aMM_bM_matrix.hpp"

// #include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
// #include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(M_aMM_bM, alias)
{
  Symmetric_Matrix<double> symM(5, 5);
  Matrix<double> M(5, 5);

  assign(symM, 1, _identity_, M, _transpose_, M, _plus_, 2, _lhs_);
}
