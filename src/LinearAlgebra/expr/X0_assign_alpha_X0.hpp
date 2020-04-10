//
// X0 = alpha * X0
// X0 = * alpha X0
//
#pragma once

#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

// specific includes
#include "LinearAlgebra/dense/matrix_transform.hpp"
#include "LinearAlgebra/dense/vector_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  //
  // X0 = alpha * X0
  // X0 = * alpha X0
  //
  template <typename ALPHA_IMPL, typename X0_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha, const _lhs_t_)
  {
    static_assert(Always_False_v<X0_IMPL>, "Undefined implementation");

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  //
  // X0 = alpha * X0
  // X0 = * alpha X0
  //
  template <typename ALPHA_IMPL, typename X0_IMPL>
  void
  assign(VMT_Crtp<X0_IMPL>& X0, const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _lhs_t_)
  {
    assign(Expr_Selector<>(), X0.impl(), _product_, alpha, _lhs_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //
  // CAVEAT: useless as _lhs_t_ is present!  -> when using low level
  // routine like assign(), the user is in charge of using the
  // canonical form.)
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
  template <typename ALPHA_IMPL, typename X0_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha, const _lhs_t_)
  {
    if (alpha.value() == 0)
    {
      assign(X0.impl(), Scalar_CRef<Element_Type_t<X0_IMPL>>(0));
      return;
    }

    if (alpha.value() != 1)
    {
      transform([&alpha](const auto& X0_component) { return alpha.value() * X0_component; },
                X0.impl());
    }
    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename ALPHA_IMPL, typename X0_IMPL>
  std::enable_if_t<Has_Static_Dimension_v<X0_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_IMPL>& X0,
         const _product_t_, const Scalar_Crtp<ALPHA_IMPL>& alpha, const _lhs_t_)
  {
    // Jump over any blas like specialization
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _product_, alpha.impl(), _lhs_);

    DEBUG_SET_SELECTED(selected);
  }
}
