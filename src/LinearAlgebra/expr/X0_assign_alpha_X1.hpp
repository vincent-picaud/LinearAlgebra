// Define: X0 = α X1
//
// CAVEAT: include X0 = α X0
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

  template <typename IMPL_X0, typename IMPL_X1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         VMT_Crtp<IMPL_X0>& X0,                                 // X0
         const Common_Element_Type_t<IMPL_X0, IMPL_X1>& alpha,  // alpha
         const VMT_Crtp<IMPL_X1>& X1                            // X1
  )
  {
    static_assert(Always_False_v<IMPL_X0>, "Undefined");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_X0, typename IMPL_X1>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<IMPL_X0>& X0,                                 // X0
         const Common_Element_Type_t<IMPL_X0, IMPL_X1>& alpha,  // alpha
         const VMT_Crtp<IMPL_X1>& X1                            // X1
  )
  {
      return assign(Expr_Selector<>(), X0.impl(), alpha, X1.impl());
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
  template <typename IMPL_X0, typename IMPL_X1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         VMT_Crtp<IMPL_X0>& X0,                                 // X0
         const Common_Element_Type_t<IMPL_X0, IMPL_X1>& alpha,  // alpha
         const VMT_Crtp<IMPL_X1>& X1                            // X1
  )
  {
    // Basic implementation for test
    fill([&alpha](const auto& X1_component) { return alpha * X1_component; }, X0.impl(), X1.impl());

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
  template <typename IMPL_X0, typename IMPL_X1>
  static inline std::enable_if_t<Any_Has_Static_Dimension_v<IMPL_X0>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         VMT_Crtp<IMPL_X0>& X0,                                 // X0
         const Common_Element_Type_t<IMPL_X0, IMPL_X1>& alpha,  // alpha
         const VMT_Crtp<IMPL_X1>& X1                            // X1
  )
  {
    // Skip dynamic BLAS like specialization
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), alpha, X1.impl());

    return selected;
  }
}
