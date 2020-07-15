#pragma once

#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/expr/copy/generic.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  //  Generic Implementation
  // ////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Matrix_Crtp<V0_IMPL>& v0,
         const Matrix_Crtp<V1_IMPL>& v1)
      -> std::enable_if_t<Always_True_v<decltype(Detail::generic_copy(v0.impl(), v1.impl()))>>
  {
    assert(dimension_predicate(v0.impl()) == dimension_predicate(v1.impl()));

    Detail::generic_copy(v0.impl(), v1.impl());

    DEBUG_SET_SELECTED(selected);
  }

  // ////////////////////////////////////////////////////////////////
  //  Blas Implementation
  // ////////////////////////////////////////////////////////////////
  //

  // ////////////////////////////////////////////////////////////////
  //  Static Implementation
  // ////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  // Role: skip Blas when dimension are static
  //
  template <typename V0_IMPL, typename V1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Matrix_Crtp<V0_IMPL>& v0,
         const Matrix_Crtp<V1_IMPL>& v1)
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>{}, v0, v1);

    DEBUG_SET_SELECTED(selected);
  }
}  // namespace LinearAlgebra
