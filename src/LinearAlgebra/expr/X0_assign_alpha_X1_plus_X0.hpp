//
// V0 = alpha * V1 + V0
// X0 = + * alpha X1 X0
//
#pragma once

#include "LinearAlgebra/expr/expr_debug.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected, VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_, const _product_t_, const Scalar_CRef<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)
  {
    static_assert(Always_False_v<X0_IMPL>, "Undefined implementation");

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * V1 + V0
  // X0 = + * alpha X1 X0
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _plus_t_, const _product_t_,
         const Scalar_CRef<ALPHA_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)

  {
    assign(Expr_Selector<>(), X0.impl(), _plus_, _product_, alpha.impl(), X1.impl(), _lhs_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_, const _product_t_, const Scalar_CRef<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)
  {
    assert(are_compatible_p(X0.impl(), X1.impl()));

    if (alpha.value() == 0)
    {
      DEBUG_SET_SELECTED(Expr_Selector_Enum::END);  // nothing to do
      return;
    }

    if (alpha.value() == 1)
    {
      transform([](const auto X0_component,
                   const auto X1_component) { return X0_component + X1_component; },
                X0.impl(), X1.impl());
    }
    else if (alpha.value() == -1)
    {
      transform([](const auto X0_component,
                   const auto X1_component) { return X0_component - X1_component; },
                X0.impl(), X1.impl());
    }
    else
    {
      transform(
          [&alpha](const auto X0_component, const auto X1_component) {
            return X0_component + alpha.value() * X1_component;
          },
          X0.impl(), X1.impl());
    }

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL, X1_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_, const _product_t_, const Scalar_CRef<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _plus_, _product_, alpha.impl(),
           X1.impl(), _lhs_);

    DEBUG_SET_SELECTED(selected);
  }
}
