#pragma once

#include "LinearAlgebra/expr/X_eq_alpha/generic_interface.hpp"

#include "LinearAlgebra/dense/matrix_fill.hpp"
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
  template <typename M0_IMPL, typename ALPHA_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Matrix_Crtp<M0_IMPL>& M0,
         const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    assign_helper(M0, alpha);

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
  template <typename M0_IMPL, typename ALPHA_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<M0_IMPL, ALPHA_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Matrix_Crtp<M0_IMPL>& M0,
         const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    assign_helper(M0, alpha);

    DEBUG_SET_SELECTED(selected);
  }
}
