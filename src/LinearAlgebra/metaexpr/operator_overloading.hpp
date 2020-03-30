//
// Overloads operators like Matrix*Vector
//
#pragma once

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Operators overloading
  //////////////////////////////////////////////////////////////////
  //
  // Allowed arguments (beside scalar)
  //
  template <typename... IMPL>
  constexpr auto Is_Supported_MetaExpr_Argument_v =
      ((Is_Crtp_Interface_Of_v<Detail::MetaExpr_Crtp, IMPL> or
        Is_Crtp_Interface_Of_v<VMT_Crtp, IMPL>)and...);

  // Product
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _product_t_,
                                             A0_IMPL, A1_IMPL>>
  operator*(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

  // scalar * Crpt<> product
  template <typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>, _product_t_,
                                             Element_Type_t<A1_IMPL>, A1_IMPL>>
  operator*(const Element_Type_t<A1_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  //
  //================================================================
  // Plus
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _plus_t_,
                                             A0_IMPL, A1_IMPL>>
  operator+(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

}
