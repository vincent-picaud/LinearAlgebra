//
// Overloads operators like Matrix*Vector
//
#pragma once

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/expr/scalar_crtp.hpp"
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

  //
  // Expr * Expr
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _product_t_,
                                             A0_IMPL, A1_IMPL>>
  operator*(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

  //
  // Scalar*Expr
  //

  // Default use Element_t
  //
  // template <typename A1_IMPL>
  // std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
  //                  Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>, _product_t_,
  //                                            Scalar_CRef<Element_Type_t<A1_IMPL>>, A1_IMPL>>
  // operator*(const Element_Type_t<A1_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  // {
  //   return {Scalar_CRef<Element_Type_t<A1_IMPL>>(arg_0), arg_1.impl()};
  // }

  template <typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>, _product_t_,
                                             Scalar_CRef<Element_Type_t<A1_IMPL>>, A1_IMPL>>
  operator*(const Scalar_CRef<Element_Type_t<A1_IMPL>>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  template <typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
      Detail::MetaExpr_BinaryOp<
          Common_Element_Type_t<Scalar_CRef<std::complex<Element_Type_t<A1_IMPL>>>, A1_IMPL>,
          _product_t_, Scalar_CRef<std::complex<Element_Type_t<A1_IMPL>>>, A1_IMPL>>
  operator*(const Scalar_CRef<std::complex<Element_Type_t<A1_IMPL>>>& arg_0,
            const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  // User overload
  template <typename USER_SCALAR, typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
      Detail::MetaExpr_BinaryOp<Common_Element_Type_t<Scalar_CRef<USER_SCALAR>, A1_IMPL>,
                                _product_t_, Scalar_CRef<USER_SCALAR>, A1_IMPL>>
  operator*(const Scalar_CRef<USER_SCALAR>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  // TODO: utiliser fallback + modify assign

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

  //
  //================================================================
  // Unary Plus
  //================================================================
  //
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>, const IMPL&>
  operator+(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  //
  //================================================================
  // Minus (binary)
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _minus_t_,
                                             A0_IMPL, A1_IMPL>>
  operator-(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

  //
  //================================================================
  // Unary minus
  //================================================================
  //
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, _unary_minus_t_, IMPL>>
  operator-(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  //////////////////////////////////////////////////////////////////
  // Transposition like unary operators
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, _transpose_t_, IMPL>>
  transpose(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, _transConj_t_, IMPL>>
  transConj(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, _conjugate_t_, IMPL>>
  conjugate(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, _identity_t_, IMPL>>
  identity(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

  //////////////////////////////////////////////////////////////////
  // Inverse unary operator
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<IMPL>,
                   Detail::MetaExpr_UnaryOp<Element_Type_t<IMPL>, _inverse_t_, IMPL>>
  inverse(const Crtp<IMPL>& arg)
  {
    return {arg.impl()};
  }

}
