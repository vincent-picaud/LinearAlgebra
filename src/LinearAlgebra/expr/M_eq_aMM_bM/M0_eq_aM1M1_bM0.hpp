//
// M0=αop(M1)op(M2)+βM0   M0=lhs, M2=rhs_1
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_debug.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // matrix0 = alpha * op1(M1) * op2(_rhs_1_) + beta * _lhs_
  // matrix0 = + * * alpha op1 matrix1 op2 matrix1 * beta _lhs_
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, Matrix_Unary_Op_Enum OP2_ENUM, typename MATRIX0_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Matrix_Crtp<MATRIX0_IMPL>& matrix0, const _plus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<MATRIX0_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _matrix_unary_op_t_<OP2_ENUM> op2, const _rhs_1_t_, const _product_t_,
         const Common_Element_Type_t<MATRIX0_IMPL, MATRIX1_IMPL>& beta, const _lhs_t_)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op1, dimension_predicate(matrix1.impl())) *
               matrix_op(op2, dimension_predicate(matrix1.impl())) ==
           dimension_predicate(matrix0.impl()));

    // Delegate computation
    //
    assign(Expr_Selector<>(), matrix0.impl(), _plus_, _product_, _product_, alpha, op1,
           matrix1.impl(), op2, _rhs_1_, _product_, beta, _lhs_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //
  // CAVEAT: as it use _lhs_t_, thus cannot be called from metaExpr, it
  //         is useless to define any alias
  //
}
