//
// V0 = alpha * V1
// X0 = * alpha X1
//
// CAVEAT: may redirect to  X0 = α X0
//
#pragma once

#include "LinearAlgebra/expr/scalar_crtp.hpp"

//----------------
//
// CAVEAT: in order to be sure of not missing any specialization, one
//         must do:
//
#include "LinearAlgebra/expr/M0_assign_alpha_M0.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_V0.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
//
//         and not simply
//
// #include "LinearAlgebra/expr/X0_assign_alpha_X0.hpp"
//
//----------------

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * V1
  // X0 = * alpha X1
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    assign(Expr_Selector<>(), X0.impl(), _product_, alpha.impl(), X1.impl());
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
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1)

  {
    if (alpha.value() == 0)
    {
      assign(X0, Scalar_CRef<Element_Type_t<ALPHA_IMPL>>(0));
      return;
    }

    if (alpha.value() == 1)
    {
      assign(X0, X1);
      return;
    }

    fill([&alpha](const auto& X1_component) { return alpha.value() * X1_component; }, X0.impl(),
         X1.impl());

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1)
  {
    // Skip dynamic BLAS like specialization
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _product_, alpha.impl(),
           X1.impl());
  }
}
