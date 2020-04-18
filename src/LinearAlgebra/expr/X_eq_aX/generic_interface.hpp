//
// Define:
//
// 1/
// X0 = alpha * X0
// X0 = * alpha X0
//
// 2/
// X0 = alpha * X1
// X0 = * alpha X1
//
// Involved subroutines:
// - copy
// - fill scalar
//
// - fill
// - transform
//
#pragma once

#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  // X0 = alpha * X0
  // X0 = * alpha X0
  //
  template <typename ALPHA_IMPL, typename X0_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _lhs_t_)
  {
    if (alpha.value() == 0)
    {
      assign(X0.impl(), alpha.impl());
    }
    else if (alpha.value() == 1)
    {
      // nothing to do
      DEBUG_SET_SELECTED(Expr_Selector_Enum::END);
    }
    else
    {
      assign(Expr_Selector<>(), X0.impl(), _product_, alpha.impl(), _lhs_);
    }
  }
  //================================================================
  // Alias
  //================================================================
  //
  // as it involves _lhs_ this expression cannot be generated by
  // Expression Template thus we do not define alias
  //

  //================================================================
  // Generic implementation that uses the VMT type
  //================================================================
  //

  template <typename ALPHA_IMPL, typename X0_IMPL>
  void
  assign_helper(VMT_Crtp<X0_IMPL>& X0, const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha,
                const _lhs_t_)
  {
    transform([&alpha](const auto X0_component) { return alpha.value() * X0_component; },
              X0.impl());
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // X0 = alpha * X1
  // X0 = * alpha X1
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    assert(dimension_predicate(X0.impl()) == dimension_predicate(X1.impl()));

    if (same_mathematical_object_p(X0.impl(), X1.impl()))
    {
      assign(X0.impl(), _product_, alpha.impl(), _lhs_);
    }
    else
    {
      if (alpha.value() == 0)
      {
        assign(X0.impl(), alpha.impl());
      }
      else if (alpha.value() == 1)
      {
        assign(X0.impl(), X1.impl());
      }
      else
      {
        assign(Expr_Selector<>(), X0.impl(), _product_, alpha.impl(), X1.impl());
      }
    }
  }

  //================================================================
  // Alias
  //================================================================
  //
  // Not needed for this simple expression
  //

  //================================================================
  // Generic implementation that uses the VMT type
  //================================================================
  //

  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign_helper(VMT_Crtp<X0_IMPL>& X0, const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha,
                const VMT_Crtp<X1_IMPL>& X1)
  {
    fill([&alpha](const auto X1_component) { return alpha.value() * X1_component; }, X0.impl(),
         X1.impl());
  }
}
