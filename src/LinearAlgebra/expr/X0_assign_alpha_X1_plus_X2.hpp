//
// V0 = alpha * V1 + V2
// X0 = + * alpha X1 X2
//
#pragma once

#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_debug.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

#include "LinearAlgebra/dense/matrix_is_same.hpp"
#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"

#include "LinearAlgebra/expr/X0_assign_alpha_X1_plus_X0.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  //////////////////////////////////////////////////////////////////q
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * V1 + V2
  // X0 = + * alpha X1 X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _plus_t_, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL, X2_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)
  {
    assert(dimension_predicate(X0.impl()) == dimension_predicate(X1.impl()));
    assert(dimension_predicate(X0.impl()) == dimension_predicate(X2.impl()));

    if (is_same(X0.impl(), X2.impl()))
    {
      // Branch to V0 = alpha * V1 + _lhs_ =  + * alpha X1 _lhs_
      //
      assign(X0.impl(), _plus_, _product_, alpha, X1.impl(), _lhs_);
    }
    else
    {
      assign(Expr_Selector<>(), X0.impl(), _plus_, _product_, alpha, X1.impl(), X2.impl());
    }
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  //
  // V0 = V1 + V2
  // X0 = + X1 X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _plus_t_, const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)
  {
    assign(X0.impl(), _plus_, _product_, 1, X1.impl(), X2.impl());
  }

  //
  // V0 = -V1 + V2
  // X0 = + - X1 X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _plus_t_, const _unary_minus_t_, const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)
  {
    assign(X0.impl(), _plus_, _product_, -1, X1.impl(), X2.impl());
  }

  //
  // V0 = V2 + alpha * V1
  // X0 = + X2 * alpha X1
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _plus_t_, const VMT_Crtp<X2_IMPL>& X2, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL, X2_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1)
  {
    assign(X0.impl(), _plus_, _product_, alpha, X1.impl(), X2.impl());
  }

  //
  // V0 = V2 - alpha * V1
  // X0 = - X2 * alpha X1
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _minus_t_, const VMT_Crtp<X2_IMPL>& X2, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL, X2_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1)
  {
    assign(X0.impl(), _plus_, _product_, -alpha, X1.impl(), X2.impl());
  }

  //
  // V0 = V2 - V1
  // X0 = - X2 X1
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _minus_t_, const VMT_Crtp<X2_IMPL>& X2,
         const VMT_Crtp<X1_IMPL>& X1)
  {
    assign(X0.impl(), _plus_, _product_, -1, X1.impl(), X2.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  //
  //
  // V0 = alpha * V1 + V2
  // X0 = + * alpha X1 X2
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL, X2_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)

  {
    // This test has already been done:
    assert(not is_same(X0.impl(), X2.impl()));  // -> axpy

    fill([&](const auto X1_component,
             const auto X2_component) { return alpha * X1_component + X2_component; },
         X0.impl(), X1.impl(), X2.impl());

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename X0_IMPL, typename X1_IMPL, typename X2_IMPL>
  std::enable_if_t<Any_Has_Static_Size_v<X0_IMPL, X1_IMPL, X2_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_IMPL>& X0,
         const _plus_t_, const _product_t_,
         const Common_Element_Type_t<X0_IMPL, X1_IMPL, X2_IMPL>& alpha, const VMT_Crtp<X1_IMPL>& X1,
         const VMT_Crtp<X2_IMPL>& X2)

  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _plus_, _product_, alpha,
           X1.impl(), X2.impl());

    DEBUG_SET_SELECTED(selected);
  }

}
