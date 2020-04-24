//
// ||x||_inf = max |x_i|
//
#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

#include <algorithm>
#include <ccomplex>
#include <cmath>
#include <limits>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL>
  void
  norm_inf(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  //
           const VMT_Crtp<IMPL>& VMT)
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL>
  auto
  norm_inf(const VMT_Crtp<IMPL>& VMT)

  {
    return norm_inf(Expr_Selector<>(), VMT.impl());
  }

  //================================================================
  //  Implementation: Scalar
  //================================================================
  //

  template <typename T>
  auto
  norm_inf(const T& alpha) -> decltype(std::abs(alpha))
  {
    using std::abs;
    
    return std::abs(alpha);
  }
  template <typename T>
  auto
  norm_inf(const std::complex<T>& alpha)
  {
    return norm_inf(alpha.real()) + norm_inf(alpha.imag());
  }

  //================================================================
  //  Generic
  //================================================================
  //

  template <typename IMPL>
  auto
  norm_inf_helper(const VMT_Crtp<IMPL>& VMT)

  {
    using std::max;

    decltype(norm_inf(std::declval<Element_Type_t<IMPL>>())) value;
    value = std::numeric_limits<decltype(value)>::lowest();

    scan([&value](const auto& c) { value = max(value, norm_inf(c)); }, VMT.impl());

    return value;
  }
}
