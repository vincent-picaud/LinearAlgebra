//
// X0 = alpha
//
#pragma once

#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface (ALWAYS generic: use VMT whenever this make sense)
  //////////////////////////////////////////////////////////////////
  //
  template <typename X0_TYPE, typename ALPHA_IMPL>
  void
  assign(VMT_Crtp<X0_TYPE>& X0, const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    assign(Expr_Selector<>(), X0.impl(), alpha.impl());
  }

  //================================================================
  // Generic implementation that uses the VMT type
  //================================================================
  //

  template <typename X0_TYPE, typename ALPHA_IMPL>
  void
  assign_helper(VMT_Crtp<X0_TYPE>& X0, const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    fill([&alpha]() { return alpha.value(); }, X0.impl());
  }
}
