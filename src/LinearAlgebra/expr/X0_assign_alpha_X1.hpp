// Define: X0 = α X1
//
// CAVEAT: include X0 = α X0
//
#pragma once

//----------------
// CAVEAT: in order to be sure of not missing any specialization, one
// must do:
#include "LinearAlgebra/expr/M0_assign_alpha_M0.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_V0.hpp"
// and not simply
// #include "LinearAlgebra/expr/X0_assign_alpha_X0.hpp"
//----------------

// #include "LinearAlgebra/expr/expr_selector.hpp"
// #include "LinearAlgebra/expr/expr_tags.hpp"

// #include "LinearAlgebra/utils/always.hpp"
// #include "LinearAlgebra/utils/element_type.hpp"
// #include "LinearAlgebra/utils/has_static_dimension.hpp"

// specific includes
// #include "LinearAlgebra/dense/vector_is_same.hpp"
// #include "LinearAlgebra/dense/vector_fill.hpp"

// #include "LinearAlgebra/dense/matrix_is_same.hpp"
// #include "LinearAlgebra/dense/matrix_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         VMT_Crtp<IMPL_DEST>& dest,                                  // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1>& alpha,  // alpha
         const VMT_Crtp<IMPL_ARG_1>& arg_1                           // arg_1
  )
  {
    static_assert(Always_False_v<IMPL_DEST>, "Undefined");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(VMT_Crtp<IMPL_DEST>& dest,                                  // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1>& alpha,  // alpha
         const VMT_Crtp<IMPL_ARG_1>& arg_1                           // arg_1
  )
  {
    // if (is_same(dest.impl(), arg_1.impl()))
    // {
    //   return assign(Expr_Selector<>(), dest.impl(), alpha, _VMT_0_);
    // }
    // else
    // {
    //   return assign(Expr_Selector<>(), dest.impl(), alpha, arg_1.impl());
    // }
    assert(0);  // Finir specialization

    return assign(Expr_Selector<>(), dest.impl(), alpha, arg_1.impl());
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
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         VMT_Crtp<IMPL_DEST>& dest,                                  // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1>& alpha,  // alpha
         const VMT_Crtp<IMPL_ARG_1>& arg_1                           // arg_1
  )
  {
    // Basic implementation for test
    fill([&alpha](const auto& arg_1_component) { return alpha * arg_1_component; }, dest.impl(),
         arg_1.impl());

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
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  static inline std::enable_if_t<Any_Has_Static_Dimension_v<IMPL_DEST, IMPL_ARG_1>,
                                 Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         VMT_Crtp<IMPL_DEST>& dest,                                  // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1>& alpha,  // alpha
         const VMT_Crtp<IMPL_ARG_1>& arg_1                           // arg_1
  )
  {
    // Skip dynamic BLAS like specialization
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), dest.impl(), alpha, arg_1.impl());

    return selected;
  }
}
