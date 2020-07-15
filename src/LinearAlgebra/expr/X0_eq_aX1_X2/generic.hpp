#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    template <typename X0_IMPL, typename ALPHA_IMPL, typename X1_IMPL, typename X2_IMPL>
    void
    generic_X0_eq_aX1_X2(VMT_Crtp<X0_IMPL>& X0,
                         const Scalar_Crtp<ALPHA_IMPL>& alpha,
                         const VMT_Crtp<X1_IMPL>& X1,
                         const VMT_Crtp<X2_IMPL>& X2)
    {
      fill([a = alpha.value()](const auto& X1_i, const auto& X2_i) { return a * X1_i + X2_i; },
           X0.impl(),
           X1.impl(),
           X2.impl());
    }
  }  // namespace Detail
}  // namespace LinearAlgebra
