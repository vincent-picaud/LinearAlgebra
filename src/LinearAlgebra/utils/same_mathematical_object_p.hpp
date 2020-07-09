// [[file:same_mathematical_object_p.org]]
#pragma once

#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  // [BEGIN_same_mathematical_object_p]
  //
  // Check if this two C++ objects represent the same mathematical
  // object (=instance representing the same data)
  //
  // - CAVEAT :: We do not try (as before) to *specialize* this function
  //   for each type pairs, this would need $O(n_\text{type}^2)$
  //   specializations! This is definitely simpler, however now *notice*
  //   that a vector and its own view do not represent the "same
  //   object".
  //
  template <typename IMPL_0, typename IMPL_1>
  constexpr bool
  same_mathematical_object_p(const Crtp<IMPL_0>& object_0, const Crtp<IMPL_1>& object_1) noexcept
  {
    return false;
  }

  template <typename IMPL>
  constexpr bool
  same_mathematical_object_p(const Crtp<IMPL>& object_0, const Crtp<IMPL>& object_1) noexcept
  {
    return &object_0.impl() == &object_1.impl();
  }
  // [END_same_mathematical_object_p]
}  // namespace LinearAlgebra
