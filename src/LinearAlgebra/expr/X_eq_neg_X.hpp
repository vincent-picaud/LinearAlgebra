// [[file:X_eq_neg_X.org]]
#pragma once

#include "LinearAlgebra/expr/X_eq_neg_X/vector.hpp"

#include "LinearAlgebra/expr/expr.hpp"

namespace LinearAlgebra
{
  // [BEGIN_assign]
  //
  // \begin{equation*}
  // X_0 = - X_1
  // \end{equation*}
  //
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(VMT_Crtp<X0_TYPE>& X0, const _unary_minus_t_, const VMT_Crtp<X1_TYPE>& X1)
  // [END_assign]
  {
    assign(Expr_Selector<>(), X0.impl(), _unary_minus_, X1.impl());
  }

}  // namespace LinearAlgebra
