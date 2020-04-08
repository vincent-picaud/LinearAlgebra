//
// V0 = alpha * V1
// X0 = * alpha X1
//
// CAVEAT: may redirect to  X0 = α X0
//
#pragma once

//----------------
//
// CAVEAT: in order to be sure of not missing any specialization, one
//         must do:
//
#include "LinearAlgebra/expr/M0_assign_alpha_M0.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_V0.hpp"
//
//         and not simply
//
// #include "LinearAlgebra/expr/X0_assign_alpha_X0.hpp"
//
//----------------


namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    static_assert(Always_False_v<X0_IMPL>, "Undefined");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * V1
  // X0 = * alpha X1
  //
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1)
  {
    return assign(Expr_Selector<>(), X0.impl(), _product_, alpha, X1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from: to:
  //

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  //
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)

  {
    if (alpha == 0)
    {
      assign(X0, 0);
    }
    else if (alpha == 1)
    {
      assign(X0, X1);
    }
    else
    {
      fill([&alpha](const auto& X1_component) { return alpha * X1_component; }, X0.impl(),
           X1.impl());
    }

    return selected;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename X0_IMPL, typename X1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Common_Element_Type_t<X0_IMPL, X1_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    // Skip dynamic BLAS like specialization
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _product_, alpha, X1.impl());

    return selected;
  }
}
