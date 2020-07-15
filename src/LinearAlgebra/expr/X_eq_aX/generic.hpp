#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    template <typename X0_IMPL, typename ALPHA_IMPL, typename X1_IMPL>
    void
    generic_X_eq_aX(VMT_Crtp<X0_IMPL>& X0,
                    const Scalar_Crtp<ALPHA_IMPL>& alpha,
                    const VMT_Crtp<X1_IMPL>& X1)
    {
      fill([a = alpha.value()](const auto& X1_i) { return a * X1_i; }, X0.impl(), X1.impl());
    }
  }  // namespace Detail
}  // namespace LinearAlgebra
