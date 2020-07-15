#pragma once

#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/expr/X_eq_neg_X/generic.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra
{
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Matrix_Crtp<V0_IMPL>& v0,
         const _unary_minus_t_,
         const Matrix_Crtp<V1_IMPL>& v1)
      -> std::enable_if_t<Always_True_v<decltype(Detail::generic_X_eq_neg_X(v0.impl(), v1.impl()))>>
  {
    Detail::generic_X_eq_neg_X(v0.impl(), v1.impl());

    DEBUG_SET_SELECTED(selected);
  }

  template <typename V0_IMPL, typename V1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Matrix_Crtp<V0_IMPL>& v0,
         const _unary_minus_t_,
         const Matrix_Crtp<V1_IMPL>& v1)
      -> std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL> and
                          Always_True_v<decltype(Detail::generic_X_eq_neg_X(v0.impl(), v1.impl()))>>
  {
    Detail::generic_X_eq_neg_X(v0.impl(), v1.impl());

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra
