//
// X0 = X0 + α X1 (Blas axpy)
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
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
         VMT_Crtp<X0_IMPL>& X0,                                // X0
         const _lhs_t_,                                        // X0
         const _plus_t_,                                       // +
         const Common_Element_Type_t<X0_IMPL, X1_IMPL> alpha,  // alpha
         const VMT_Crtp<X1_IMPL>& X1                           // X1
  )
  {
    static_assert(Always_False_v<X0_IMPL>, "Undefined implementation");
    return Expr_Selector_Enum::Undefined;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,                                // X0
         const _lhs_t_,                                        // X0
         const _plus_t_,                                       // +
         const Common_Element_Type_t<X0_IMPL, X1_IMPL> alpha,  // alpha
         const VMT_Crtp<X1_IMPL>& X1                           // X1
  )
  {
    return assign(Expr_Selector<>(), X0.impl(), _lhs_, _plus_, alpha, X1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from: X0 = X0 + α X1
  // to  : X0 = α X1 + X0
  //
  template <typename X0_IMPL, typename X1_IMPL>
  Expr_Selector_Enum
  assign(VMT_Crtp<X0_IMPL>& X0,                                // X0
         const Common_Element_Type_t<X0_IMPL, X1_IMPL> alpha,  // alpha
         const VMT_Crtp<X1_IMPL>& X1,                          // X1
         const _plus_t_,                                       // +
         const _lhs_t_                                         // X0
  )
  {
    return assign(X0.impl(), _lhs_, _plus_, alpha, X1.impl());
  }

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
  assign(const Expr_Selector<Expr_Selector_Enum::Generic>&,    // Generic implementation
         VMT_Crtp<X0_IMPL>& X0,                                // X0
         const _lhs_t_,                                        // X0
         const _plus_t_,                                       // +
         const Common_Element_Type_t<X0_IMPL, X1_IMPL> alpha,  // alpha
         const VMT_Crtp<X1_IMPL>& X1                           // X1
  )
  {
    transform([&alpha](const auto X0_component,
                       const auto X1_component) { return X0_component + alpha * X1_component; },
              X0.impl(), X1.impl());

    // assert(are_compatible_p(X0.storage_scheme(), X1.storage_scheme()));

    // if (alpha == 0)
    // {
    //   return Expr_Selector_Enum::Generic;  // nothing to do
    // }

    // if ((void*)&X0 == (void*)&X1.impl())
    // {
    //   return assign(X0, 1 + alpha, _lhs_);
    // }

    // if (alpha == 1)
    // {
    //   transform([](const auto X0_component, const auto v1_i) { return X0_component + v1_i; }, X0.impl(),
    //             X1.impl());
    // }
    // else if (alpha == -1)
    // {
    //   transform([](const auto X0_component, const auto v1_i) { return X0_component - v1_i; }, X0.impl(),
    //             X1.impl());
    // }
    // else
    // {
    //   transform(
    //       [alpha](const auto X0_component, const auto v1_i) { return X0_component + alpha * v1_i; },
    //       X0.impl(), X1.impl());
    // }

    return Expr_Selector_Enum::Generic;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)

#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename X0_IMPL, typename X1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL, X1_IMPL>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         VMT_Crtp<X0_IMPL>& X0,                                // X0
         const _lhs_t_,                                        // X0
         const _plus_t_,                                       // +
         const Common_Element_Type_t<X0_IMPL, X1_IMPL> alpha,  // alpha
         const VMT_Crtp<X1_IMPL>& X1                           // X1
  )
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), _lhs_, _plus_, alpha,
           X1.impl());

    return selected;
  }
}
