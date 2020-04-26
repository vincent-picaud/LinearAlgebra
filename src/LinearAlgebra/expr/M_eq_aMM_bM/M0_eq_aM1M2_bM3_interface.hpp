//
// M0=αop(M1)op(M2)+βM0   M0=lhs
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/expr/scalar_crtp.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  // The generic interface:
  //
  // matrix0 = alpha * transpose(matrix1) * transpose(matrix2) + beta * matrix3
  // matrix0 = + * * alpha op1 matrix1 op2 matrix2 * beta matrix3
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM,
            Matrix_Unary_Op_Enum OP2_ENUM,
            typename ALPHA_IMPL,
            typename BETA_IMPL,
            typename MATRIX0_IMPL,
            typename MATRIX1_IMPL,
            typename MATRIX2_IMPL,
            typename MATRIX3_IMPL>
  void
  assign(Matrix_Crtp<MATRIX0_IMPL>& matrix0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _matrix_unary_op_t_<OP2_ENUM> op2,
         const Matrix_Crtp<MATRIX2_IMPL>& matrix2,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Matrix_Crtp<MATRIX3_IMPL>& matrix3)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(matrix0.impl()) =
               matrix_op(op1, dimension_predicate(matrix1.impl())) *
                   matrix_op(op2, dimension_predicate(matrix2.impl())) +
               dimension_predicate(matrix3.impl()));

    // Delegate computation
    //
    assert(0);
    // assign(Expr_Selector<>(),
    //        matrix0.impl(),
    //        _plus_,
    //        _product_,
    //        _product_,
    //        alpha,
    //        op1,
    //        matrix1.impl(),
    //        op2,
    //        matrix2.impl(),
    //        _product_,
    //        beta,
    //        matrix3.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //
  // CAVEAT: as it use _lhs_t_, thus cannot be called from metaExpr, it
  //         is useless to define any alias
  //
}  // namespace LinearAlgebra
