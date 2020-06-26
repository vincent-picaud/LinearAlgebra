// file:assign_fallback.org
#pragma once

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  // [BEGIN_Fallback]
  //
  template <typename DEST_IMPL, typename... ARG_IMPL>
  void
  assign(Crtp<DEST_IMPL>&, const Crtp<ARG_IMPL>&...)
  {
    static_assert(Always_False_v<DEST_IMPL>, "Unknown Pattern");
  }

  template <typename DEST_IMPL, typename... ARG_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Crtp<DEST_IMPL>&,
         const Crtp<ARG_IMPL>&...)
  {
    static_assert(Always_False_v<DEST_IMPL>, "Known Pattern, Unknown specialization ");
  }
    // [END_Fallback]
}
