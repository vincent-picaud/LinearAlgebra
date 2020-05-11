//
// Compute min & max
//
#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

#include <algorithm>
#include <limits>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  // For these functions, we only provide one implementation (no
  // Expr_Selector, etc...), which is defined as follows:
  //
  template <typename IMPL>
  auto
  min(const VMT_Crtp<IMPL>& VMT)
  {
    using std::min;

    Element_Type_t<IMPL> value;
    value = std::numeric_limits<decltype(value)>::max();

    scan([&value](const auto& c) { value = min(value, c); }, VMT.impl());

    return value;
  }
  template <typename IMPL>
  auto
  max(const VMT_Crtp<IMPL>& VMT)

  {
    using std::max;

    Element_Type_t<IMPL> value;
    value = std::numeric_limits<decltype(value)>::lowest();

    scan([&value](const auto& c) { value = max(value, c); }, VMT.impl());

    return value;
  }
}  // namespace LinearAlgebra
