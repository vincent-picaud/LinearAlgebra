/** 
    Defines \f$ x_0 = \alpha x_1 \f$ pattern

    @file
    @ingroup Group_Vector_Patterns
    @ingroup Group_Matrix_Patterns
*/
#pragma once

#include "LinearAlgebra/expr/X_eq_aX/matrix.hpp"
#include "LinearAlgebra/expr/X_eq_aX/vector.hpp"

#include "LinearAlgebra/expr/expr.hpp"

namespace LinearAlgebra
{
  /** 
      Master \f$ X_0 = \alpha X_1 \f$
   */
  template <typename X0_TYPE, typename ALPHA_IMPL, typename X1_TYPE>
  void
  assign(VMT_Crtp<X0_TYPE>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_TYPE>& X1)
  {
    assign(Expr_Selector<>(), X0.impl(), _product_, alpha.impl(), X1.impl());
  }

}  // namespace LinearAlgebra
