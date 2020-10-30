/** 
    Defines \f$ x_0 = - x_1 \f$ pattern

    @file
    @ingroup Group_Vector_Patterns
    @ingroup Group_Matrix_Patterns
*/
#pragma once

#include "LinearAlgebra/expr/X_eq_neg_X/matrix.hpp"
#include "LinearAlgebra/expr/X_eq_neg_X/vector.hpp"

#include "LinearAlgebra/expr/expr.hpp"

namespace LinearAlgebra
{
  /** Master \f$ x_0 = - x_1 \f$
   */
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(VMT_Crtp<X0_TYPE>& X0, const _unary_minus_t_, const VMT_Crtp<X1_TYPE>& X1)
  {
    assign(Expr_Selector<>(), X0.impl(), _unary_minus_, X1.impl());
  }

}  // namespace LinearAlgebra
