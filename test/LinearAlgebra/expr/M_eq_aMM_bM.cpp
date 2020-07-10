#include "LinearAlgebra/matrix.hpp"

#include "LinearAlgebra/expr/M_eq_aMM_bM.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;
TEST(M_aMM_bM, Gemm_with_lhs)
{
  Matrix<double> M0(5, 5);
  Matrix<double> M1(5, 5);
  Matrix<double> M2(5, 5);

  assign(M0,
         _plus_,
         _product_,
         _product_,
         Scalar<int>(1),
         _identity_,
         M1,
         _transpose_,
         M2,
         _product_,
         Scalar<int>(2),
         M0);

  //  M = 1 * M1 * M2 + 2 * M;
}

// TEST(M_aMM_bM, Symmetric_rank_1)
// {
//   Symmetric_Matrix<double> symM(5, 5);
//   Matrix<double> M(5, 5);

//   assign(symM,
//          _plus_,
//          _product_,
//          _product_,
//          1,
//          _identity_,
//          M,
//          _transpose_,
//          _rhs_1_,
//          _product_,
//          2,
//          _lhs_);
// }
