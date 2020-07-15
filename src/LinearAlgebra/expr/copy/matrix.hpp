#pragma once

#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  //  Generic Implementation
  // ////////////////////////////////////////////////////////////////
  //
  template <typename M0_IMPL, typename M1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Matrix_Crtp<M0_IMPL>& M0,
         const Dense_Matrix_Crtp<M1_IMPL>& M1)
  {
    assert(dimension_predicate(M0.impl()) == dimension_predicate(M1.impl()));

    fill([](const auto X1_component) { return X1_component; }, M0.impl(), M1.impl());

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
  template <typename M0_IMPL, typename M1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<M0_IMPL, M1_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Matrix_Crtp<M0_IMPL>& M0,
         const Dense_Matrix_Crtp<M1_IMPL>& M1)
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>{}, M0, M1);

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra
