//
// V0 = α op(M) V1 + β V0
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * transpose(M1) * V1 + beta * V0
  // vector0 = + * * alpha op1 matrix1 vector1 * beta vector0
  //
  template <typename ALPHA_IMPL, typename BETA_IMPL, Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_, const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha, const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_, const Scalar_Crtp<BETA_IMPL>& beta, const _lhs_t_)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op1, dimension_predicate(matrix1)) * dimension_predicate(vector1) +
           dimension_predicate(vector0));

    // Delegate computation
    //
    assign(Expr_Selector<>(), vector0.impl(), _plus_, _product_, _product_, alpha.impl(), op1,
           matrix1.impl(), vector1.impl(), _product_, beta.impl(), _lhs_);
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
