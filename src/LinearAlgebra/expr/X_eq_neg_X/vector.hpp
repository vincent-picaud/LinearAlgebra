#pragma once

#include "LinearAlgebra/dense/vector_fwd.hpp"
#include "LinearAlgebra/expr/X_eq_neg_X/generic.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Vector_Crtp<V0_IMPL>& v0,
         const _unary_minus_t_,
         const Vector_Crtp<V1_IMPL>& v1)
      -> std::enable_if_t<Always_True_v<decltype(Detail::generic_X_eq_neg_X(v0.impl(), v1.impl()))>>
  {
    Detail::generic_X_eq_neg_X(v0.impl(), v1.impl());
  }

}  // namespace LinearAlgebra
