#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_debug.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename V1_IMPL>
  void
  dist_2(const Expr_Selector<Expr_Selector_Enum::Undefined>,  //
         const VMT_Crtp<V0_IMPL>& V0,                         //
         const VMT_Crtp<V1_IMPL>& V1                          //
  )
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Undefined);

    static_assert(Always_False_v<V0_IMPL>, "Undefined implementation");
  }

  template <typename V0_IMPL, typename V1_IMPL>
  void
  squared_dist_2(const Expr_Selector<Expr_Selector_Enum::Undefined>,  //
                 const VMT_Crtp<V0_IMPL>& V0,                         //
                 const VMT_Crtp<V1_IMPL>& V1                          //
  )
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Undefined);

    static_assert(Always_False_v<V0_IMPL>, "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  dist_2(const VMT_Crtp<V0_IMPL>& V0,  //
         const VMT_Crtp<V1_IMPL>& V1   //
  )
  {
    assert(dimension_predicate(V0.impl()) == dimension_predicate(V1.impl()));
    return dist_2(Expr_Selector<>(), V0.impl(), V1.impl());
  }

  template <typename V0_IMPL, typename V1_IMPL>
  auto
  squared_dist_2(const VMT_Crtp<V0_IMPL>& V0,  //
                 const VMT_Crtp<V1_IMPL>& V1   //
  )
  {
    assert(dimension_predicate(V0.impl()) == dimension_predicate(V1.impl()));
    return squared_dist_2(Expr_Selector<>(), V0.impl(), V1.impl());
  }
}
