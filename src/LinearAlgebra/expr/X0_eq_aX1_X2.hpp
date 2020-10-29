/** 
    Defines \f$ x_0 = \alpha x_1 + x_2 \f$ pattern familly

    @file
    @ingroup Group_Vector
    @ingroup Group_Matrix
*/
#pragma once

#include "LinearAlgebra/expr/X0_eq_aX1_X2/matrix.hpp"
#include "LinearAlgebra/expr/X0_eq_aX1_X2/vector.hpp"

#include "LinearAlgebra/expr/expr.hpp"

namespace LinearAlgebra
{
  /** Master \f$ x_0 = \alpha x_1 + x_2 \f$
   */
  template <typename X0_IMPL, typename ALPHA_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)
  {
    // note: do not check X0 as there is still the opportunity to resize it
    assert(dimension_predicate(X1.impl()) == dimension_predicate(X2.impl()));

    assign(Expr_Selector<>(), X0.impl(), _plus_, _product_, alpha.impl(), X1.impl(), X2.impl());
  }

  // ////////////////////////////////////////////////////////////////
  // Alias
  // ////////////////////////////////////////////////////////////////

  /** Alias \f$ x_0 = x_2 + \alpha x_1 \f$
   */
  template <typename X0_IMPL, typename X2_IMPL, typename ALPHA_IMPL, typename X1_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_,
         const VMT_Crtp<X2_IMPL>& X2,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    assign(X0.impl(), _plus_, _product_, alpha.impl(), X1.impl(), X2.impl());
  }

  /** Alias \f$ x_0 = x_2 - \alpha x_1 \f$
   */
  template <typename X0_IMPL, typename X2_IMPL, typename ALPHA_IMPL, typename X1_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0,
         const _minus_t_,
         const VMT_Crtp<X2_IMPL>& X2,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    assign(X0.impl(), _plus_, _product_, ALPHA_IMPL{-alpha.value()}, X1.impl(), X2.impl());
  }

}  // namespace LinearAlgebra
