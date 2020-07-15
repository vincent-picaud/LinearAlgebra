// [[file:X0_eq_aX1_X2.org]]
#pragma once

#include "LinearAlgebra/expr/X0_eq_aX1_X2/matrix.hpp"
#include "LinearAlgebra/expr/X0_eq_aX1_X2/vector.hpp"

#include "LinearAlgebra/expr/expr.hpp"

namespace LinearAlgebra
{
  // [BEGIN_assign]
  //
  // \begin{equation*}
  // v_0 = \alpha v_1 + v_2
  // \end{equation*}
  //
  template <typename X0_IMPL, typename ALPHA_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)
  // [END_assign]

  {
    // note: do not check X0 as there is still the opportunity to resize it
    assert(dimension_predicate(X1.impl()) == dimension_predicate(X2.impl()));

    assign(Expr_Selector<>(), X0.impl(), _plus_, _product_, alpha.impl(), X1.impl(), X2.impl());
  }

  // ////////////////////////////////////////////////////////////////
  // Alias
  // ////////////////////////////////////////////////////////////////

  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = v_2 + \alpha v_1
  // \end{equation*}
  // [END_alias]
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
  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = v_2 - \alpha v_1
  // \end{equation*}
  // [END_alias]
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
