#pragma once

#include "LinearAlgebra/expr/copy/generic_interface.hpp"

#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/expr/expr.hpp"
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
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Matrix_Crtp<X0_TYPE>& X0,
         const Dense_Matrix_Crtp<X1_TYPE>& X1)
  {
    assign_helper(X0, X1);

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
  // Not yet
  //

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  // Role: skip Blas when dimension are static
  //
  template <typename X0_TYPE, typename X1_TYPE>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_TYPE, X1_TYPE>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Matrix_Crtp<X0_TYPE>& X0,
         const Dense_Matrix_Crtp<X1_TYPE>& X1)
  {
    assign_helper(X0, X1);

    DEBUG_SET_SELECTED(selected);
  }
}
