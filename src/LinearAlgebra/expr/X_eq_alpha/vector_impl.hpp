#pragma once

#include "LinearAlgebra/expr/X_eq_alpha/generic_interface.hpp"

#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename V0_IMPL, typename ALPHA_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, Dense_Vector_Crtp<V0_IMPL>& V0,
         const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    assign_helper(V0, alpha);

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
  // Role: skip Blas when dimension are static
  //
  template <typename V0_IMPL, typename ALPHA_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, ALPHA_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, Dense_Vector_Crtp<V0_IMPL>& V0,
         const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    assign_helper(V0, alpha);

    DEBUG_SET_SELECTED(selected);
  }
}
