//
// ||x||_2 and ||x||_2^2
//
#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/utils/always.hpp"

#include <ccomplex>
#include <cmath>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL>
  void
  squared_norm_2(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  //
                 const VMT_Crtp<IMPL>& VMT)
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");
  }

  template <typename IMPL>
  void
  norm_2(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  //
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
  squared_norm_2(const VMT_Crtp<IMPL>& VMT)

  {
    return squared_norm_2(Expr_Selector<>(), VMT.impl());
  }

  template <typename IMPL>
  auto
  norm_2(const VMT_Crtp<IMPL>& VMT)

  {
    return norm_2(Expr_Selector<>(), VMT.impl());
  }

  //================================================================
  //  Implementation: Scalar
  //================================================================
  //

  template <typename T>
  auto
  norm_2(const T& alpha) -> decltype(std::abs(alpha))
  {
    return std::abs(alpha);
  }

  template <typename T>
  auto
  squared_norm_2(const T& alpha) -> decltype(std::pow(norm_2(alpha), 2))
  {
    return std::pow(norm_2(alpha), 2);
  }

}
