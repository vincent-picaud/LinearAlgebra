// [[file:copy.org]]
#pragma once

#include "LinearAlgebra/dense/vmt_crtp.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

#include "LinearAlgebra/expr/copy/vector.hpp"
#include "LinearAlgebra/expr/copy/matrix.hpp"

namespace LinearAlgebra
{
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(VMT_Crtp<X0_TYPE>& X0,       // X0
         const VMT_Crtp<X1_TYPE>& X1  // X1
  )
  {
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
}  // namespace LinearAlgebra
