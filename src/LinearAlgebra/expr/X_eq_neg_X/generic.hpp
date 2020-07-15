#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    template <typename X0_IMPL, typename X1_IMPL>
    void
    generic_X_eq_neg_X(VMT_Crtp<X0_IMPL>& X0, const VMT_Crtp<X1_IMPL>& X1)
    {
      fill([](const auto& X1_i) { return -X1_i; }, X0.impl(), X1.impl());
    }
  }  // namespace Detail
}  // namespace LinearAlgebra
