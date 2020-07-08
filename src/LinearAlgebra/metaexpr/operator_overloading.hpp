//
// Overloads operators like Matrix*Vector
//
#pragma once

#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/expr/scalar_crtp.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp.hpp"
#include "LinearAlgebra/utils/complex.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Operators overloading
  //////////////////////////////////////////////////////////////////
  //
  // Allowed arguments (beside scalar)
  //
  // Design note: this will let you create meaningless expression like "Matrix + Vector"
  //
  //              if we wanted enforce/restrict expressions like
  //              "Matrix+Matrix" or "Vector+Vector" we would have had
  //              to embed the "is a vector" or "is a matrix"
  //              information into the MetaExpr_BinaryOp class. This
  //              would have leaded to more complex and less reusable
  //              Operator classes. This is the reason why (and I
  //              think that's a good decision) we do not perform such
  //              filtering here.
  //
  // Here: filter arbitrary Expression involving arbitrary
  // VMT=Vector/Matrix/Tensor
  //
  template <typename... IMPL>
  constexpr auto Is_Supported_MetaExpr_Argument_v =
      ((Is_Crtp_Interface_Of_v<Detail::MetaExpr_Crtp, IMPL> or
        Is_Crtp_Interface_Of_v<VMT_Crtp, IMPL>)and...);

  //================================================================
  // Product
  //================================================================
  //

  //----------------------------------------------------------------
  // Expr * Expr
  //----------------------------------------------------------------
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
      Detail::
          MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _product_t_, A0_IMPL, A1_IMPL>>
  operator*(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

  //----------------------------------------------------------------
  // Scalar*Expr
  //----------------------------------------------------------------
  //

  // CAVEAT: dangling references
  //
  // You must NOT write:
  //
  // template <typename A1_IMPL>
  // std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
  //                  Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>, _product_t_,
  //                                            Scalar<Element_Type_t<A1_IMPL>>, A1_IMPL>>
  // operator*(const Element_Type_t<A1_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  // {
  //   return {Scalar<Element_Type_t<A1_IMPL>>(arg_0), arg_1.impl()};
  // }
  //
  // as this creates a:
  //
  // DANGLING REFERENCE: return {Scalar<Element_Type_t<A1_IMPL>>(arg_0) <-- here, arg_1.impl()};
  //
  //

  // Handle expression like: T * Vector<T>
  template <typename A1_IMPL>
  std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
                   Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>,
                                             _product_t_,
                                             Scalar<Element_Type_t<A1_IMPL>>,
                                             A1_IMPL>>
  operator*(const Scalar<Element_Type_t<A1_IMPL>>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  // Handle expression like: U* Vector<T>,
  //
  // where U = Scalar<USER_SCALAR>
  //
  // -> user must _explicitly_ define the scalar type
  //
  template <typename USER_SCALAR, typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A1_IMPL> and
          // remove some ambiguities
          not std::is_same_v<USER_SCALAR, Element_Type_t<A1_IMPL>>,
      Detail::MetaExpr_BinaryOp<Common_Element_Type_t<Scalar<USER_SCALAR>, A1_IMPL>,
                                _product_t_,
                                Scalar<USER_SCALAR>,
                                A1_IMPL>>
  operator*(const Scalar<USER_SCALAR>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  // NEW
  // template <typename A1_IMPL>
  // std::enable_if_t<Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
  //                  Detail::MetaExpr_BinaryOp<Element_Type_t<A1_IMPL>,
  //                                            _product_t_,
  //                                            Scalar<Element_Type_t<A1_IMPL>>,
  //                                            A1_IMPL>>
  // operator*(const Element_Type_t<A1_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  // {
  //   return {Scalar<Element_Type_t<A1_IMPL>>{arg_0}, arg_1.impl()};
  // }
  // template <typename USER_SCALAR, typename A1_IMPL>
  // std::enable_if_t<
  //     Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
  //     Detail::MetaExpr_BinaryOp<Common_Element_Type_t<Scalar<USER_SCALAR>, A1_IMPL>,
  //                               _product_t_,
  //                               Scalar<USER_SCALAR>,
  //                               A1_IMPL>>
  // operator*(const Scalar<USER_SCALAR>& arg_0, const Crtp<A1_IMPL>& arg_1)
  // {
  //   return {arg_0, arg_1.impl()};
  // }

  //----------------------------------------------------------------
  // std::complex
  //----------------------------------------------------------------
  //
  // Note: follow the same scheme to adapt this to AD<T> autodiff
  //

  // Handle expression like: complex<T> * Vector<T>
  template <typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
      Detail::MetaExpr_BinaryOp<
          Common_Element_Type_t<Scalar<std::complex<Element_Type_t<A1_IMPL>>>, A1_IMPL>,
          _product_t_,
          Scalar<std::complex<Element_Type_t<A1_IMPL>>>,
          A1_IMPL>>
  operator*(const Scalar<std::complex<Element_Type_t<A1_IMPL>>>& arg_0,
            const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  template <typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A1_IMPL> && Is_Complex_v<Element_Type_t<A1_IMPL>>,
      Detail::MetaExpr_BinaryOp<
          Common_Element_Type_t<Scalar<typename Element_Type_t<A1_IMPL>::value_type>, A1_IMPL>,
          _product_t_,
          Scalar<typename Element_Type_t<A1_IMPL>::value_type>,
          A1_IMPL>>
  operator*(const Scalar<typename Element_Type_t<A1_IMPL>::value_type>& arg_0,
            const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0, arg_1.impl()};
  }

  // New
  // template <typename A1_IMPL>
  // std::enable_if_t<
  //     Is_Supported_MetaExpr_Argument_v<A1_IMPL>,
  //     Detail::MetaExpr_BinaryOp<
  //         Common_Element_Type_t<Scalar<std::complex<Element_Type_t<A1_IMPL>>>, A1_IMPL>,
  //         _product_t_,
  //         Scalar<std::complex<Element_Type_t<A1_IMPL>>>,
  //         A1_IMPL>>
  // operator*(const std::complex<Element_Type_t<A1_IMPL>>& arg_0, const Crtp<A1_IMPL>& arg_1)
  // {
  //   return {Scalar<std::complex<Element_Type_t<A1_IMPL>>>{arg_0}, arg_1.impl()};
  // }

  //----------------------------------------------------------------
  // std::complex END
  //----------------------------------------------------------------

  //================================================================
  // Plus
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
      Detail::
          MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _plus_t_, A0_IMPL, A1_IMPL>>
  operator+(const Crtp<A0_IMPL>& arg_0, const Crtp<A1_IMPL>& arg_1)
  {
    return {arg_0.impl(), arg_1.impl()};
  }

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

  //================================================================
  // Minus (binary)
  //================================================================
  //
  template <typename A0_IMPL, typename A1_IMPL>
  std::enable_if_t<
      Is_Supported_MetaExpr_Argument_v<A0_IMPL, A1_IMPL>,
      Detail::
          MetaExpr_BinaryOp<Common_Element_Type_t<A0_IMPL, A1_IMPL>, _minus_t_, A0_IMPL, A1_IMPL>>
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

}  // namespace LinearAlgebra
