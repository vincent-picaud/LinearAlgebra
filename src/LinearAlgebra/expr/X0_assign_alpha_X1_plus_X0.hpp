//
// V0 = alpha * V1 + V0
// X0 = + * alpha X1 X0
//
#pragma once

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
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined>, VMT_Crtp<X0_IMPL>& X0, const _plus_t_,
         const _product_t_, const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)
  {
    static_assert(Always_False_v<X0_IMPL>, "Undefined implementation");
    return Expr_Selector_Enum::Undefined;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * V1 + V0
  // X0 = + * alpha X1 X0
  //
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0, const _plus_t_, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1,
         const _lhs_t_)

  {
    return assign(Expr_Selector<>(), X0.impl(), _plus_, _product_, alpha, X1.impl(), _lhs_);
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
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_IMPL>& X0, const _plus_t_,
         const _product_t_, const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)
  {
    assert(are_compatible_p(X0.impl(), X1.impl()));

    if (alpha == 0)
    {
      return Expr_Selector_Enum::END;  // nothing to do
    }

    if (alpha == 1)
    {
      transform([](const auto X0_component,
                   const auto X1_component) { return X0_component + X1_component; },
                X0.impl(), X1.impl());
    }
    else if (alpha == -1)
    {
      transform([](const auto X0_component,
                   const auto X1_component) { return X0_component - X1_component; },
                X0.impl(), X1.impl());
    }
    else
    {
      transform([&alpha](const auto X0_component,
                         const auto X1_component) { return X0_component + alpha * X1_component; },
                X0.impl(), X1.impl());
    }

    return Expr_Selector_Enum::Generic;
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename X0_IMPL, typename X1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL, X1_IMPL>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_, const _product_t_, const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1, const _lhs_t_)
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _plus_, _product_, alpha,
           X1.impl(), _lhs_);

    return selected;
  }
}
