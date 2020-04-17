//
// X0 = X1
//
// Note: this file also explains our design
//
#pragma once

#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface (ALWAYS generic: use VMT whenever this make sense)
  //////////////////////////////////////////////////////////////////
  //
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(VMT_Crtp<X0_TYPE>& X0,       // X0
         const VMT_Crtp<X1_TYPE>& X1  // X1
  )
  {
    assert(dimension_predicate(X0.impl()) == dimension_predicate(X1.impl()));

    // Something to do?
    if (not same_mathematical_object_p(X0.impl(), X1.impl()))
    {
      assign(Expr_Selector<>(), X0.impl(), X1.impl());
    }
    else
    {
      DEBUG_SET_SELECTED(Expr_Selector_Enum::END);
    }
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  // IMPORTANT NOTE: despite the presence of Expr_Selector<> there are
  //                 ambiguities between (1), (2), (3) in a scheme
  //                 like this one:
  //
  // (1) Generic (for VMT)
  // template <typename X0_TYPE, typename X1_TYPE>
  // void
  // assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<X0_TYPE>& X0,
  //        const VMT_Crtp<X1_TYPE>& X1) { ... }
  //
  // (2) Blas (for vector)
  // template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  // auto
  // assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
  //        Dense_Vector_Crtp<VECTOR_0_TYPE>& vector_0,
  //        const Dense_Vector_Crtp<VECTOR_1_TYPE>& vector_1) std::enable_if<ok for blas::cpy> { ... }
  //
  // (3) Static (for VMT)
  // template <typename X0_TYPE, typename X1_TYPE>
  // std::enable_if_t<Any_Has_Static_Dimension_v<X0_TYPE, X1_TYPE>>
  // assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<X0_TYPE>& X0,
  //        const VMT_Crtp<X1_TYPE>& X1) { ... }
  //
  //                  The reason is that several conversions are
  //                  involved:
  //
  //                  1. Expr_Selector<Static> -> Expr_Selector<Blas> -> Expr_Selector<Generic>
  //
  //                  but also
  //
  //                  2. VMT -> Dense_Vector
  //
  // THE SOLUTION is to use (for the implementation part, that is the
  //              "assign(const Expr_Selector<...>, Vector<> ...)"
  //              functions) the *same type Vector everywhere*.
  //
  //              However as we must do the same for Matrix etc.
  //              "assign(const Expr_Selector<...>, Matrix<> ...)"  this
  //              introduce REDUNDANT code.
  //
  //              That is the reason why we can also define functions
  //              like "assign_helper_XXX(VMT<> ...)"  to factorize
  //              this code.
  //
  //              -> see file vector_impl.hpp and matrix_imp.hpp for a
  //              -> concrete example.
  //
  // NOTE: the interface part (that is the functions "assign(...)"
  //       that don't involve Expr_Selector) obviously remain generic
  //       (they use VMT type).

  //================================================================
  // Generic implementation that uses the VMT type
  //================================================================
  //

  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign_helper(VMT_Crtp<X0_TYPE>& X0, const VMT_Crtp<X1_TYPE>& X1)
  {
    fill([](const auto X1_component) { return X1_component; }, X0.impl(), X1.impl());
  }
}
