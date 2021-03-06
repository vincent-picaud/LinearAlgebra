//
// Notations:
//
// arg_0 = arg_1 op arg_2....
//
// arg_0      is ALWAYS the LHS
// arg_i, i>0 belongs to the RHS, i denotes the rank of the first occurrence
//
// Example:
//
//            assign(M, v, transpose(_lhs_1_), _plus_, _rhs_);
//
//   is translated into
//
//             M = M + v.v^t
//
// CAVEAT: _product_ is not noted.
//
//         However, please note that special products like
//         (_cwise_product_, _Kronecker_product_) are noted.
//
#pragma once

#include "LinearAlgebra/utils/complex.hpp"
#include "LinearAlgebra/utils/crtp.hpp"

namespace LinearAlgebra
{
  ///////////////////////////////////////////////////////
  // Tags as CRTP for generic filtering
  ///////////////////////////////////////////////////////
  //
  // [BEGIN_Expr_Tags_Crtp]
  //
  // Crtp base class used by:
  // - tags
  // - operator unary, binary
  //
  template <typename IMPL>
  class Expr_Tags_Crtp : public Crtp_Find_Impl<Expr_Tags_Crtp, IMPL, Crtp>
  {
  };
  // [END_Expr_Tags_Crtp]

  ///////////////////////////////////////////////////////
  //
  // Note: as we do not use capitalized first letter these are LEGAL
  //       C++ identifiers, see
  //       https://en.cppreference.com/w/cpp/language/identifiers
  //
  // [BEGIN_Expr_Tags]
  //
  // Tags used to notify operations (plus, product...)
  //
  struct _plus_t_ final : Expr_Tags_Crtp<_plus_t_>
  {
  };
  constexpr auto _plus_ = _plus_t_();

  struct _minus_t_ final : Expr_Tags_Crtp<_minus_t_>
  {
  };
  constexpr auto _minus_ = _minus_t_();

  struct _unary_minus_t_ final : Expr_Tags_Crtp<_unary_minus_t_>
  {
  };
  constexpr auto _unary_minus_ = _unary_minus_t_();

  struct _product_t_ final : Expr_Tags_Crtp<_product_t_>
  {
  };
  constexpr auto _product_ = _product_t_();

  struct _inverse_t_ final : Expr_Tags_Crtp<_inverse_t_>
  {
  };
  constexpr auto _inverse_ = _inverse_t_();

  struct _assign_t_ final : Expr_Tags_Crtp<_assign_t_>
  {
  };
  constexpr auto _assign_ = _assign_t_();

  // [DOC]
  //
  // Tags used to notify argument
  //
  struct _lhs_t_ final : Expr_Tags_Crtp<_lhs_t_>
  {
  };
  struct _rhs_1_t_ final : Expr_Tags_Crtp<_rhs_1_t_>
  {
  };
  struct _rhs_2_t_ final : Expr_Tags_Crtp<_rhs_2_t_>
  {
  };

  constexpr auto _lhs_   = _lhs_t_();
  constexpr auto _rhs_1_ = _rhs_1_t_();
  constexpr auto _rhs_2_ = _rhs_2_t_();

  // [END_Expr_Tags]

  //----------------------------------------------------------------

  //////////////////////////////////////////////
  // Matrix unary operators (like transpose) //
  /////////////////////////////////////////////
  //
  enum class Matrix_Unary_Op_Enum
  {
    Transpose,
    Conjugate,
    TransConj,
    Identity
  };

  template <Matrix_Unary_Op_Enum OP>
  struct _matrix_unary_op_t_ final : Expr_Tags_Crtp<_matrix_unary_op_t_<OP>>
  {
  };

  template <Matrix_Unary_Op_Enum OP_A, Matrix_Unary_Op_Enum OP_B>
  constexpr bool
  operator==(const _matrix_unary_op_t_<OP_A>, const _matrix_unary_op_t_<OP_B>) noexcept
  {
    return OP_A == OP_B;
  }

  using _identity_t_  = _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>;
  using _transpose_t_ = _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>;
  using _conjugate_t_ = _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>;
  using _transConj_t_ = _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>;

  constexpr auto _identity_  = _identity_t_();
  constexpr auto _transpose_ = _transpose_t_();
  constexpr auto _conjugate_ = _conjugate_t_();
  constexpr auto _transConj_ = _transConj_t_();

  ///////////////////////////////////////////////////
  // Does _matrix_unary_op_t_ modifies dimensions? //
  ///////////////////////////////////////////////////
  //
  template <Matrix_Unary_Op_Enum OP>
  constexpr bool
  does_it_transpose_matrix_dimension(const _matrix_unary_op_t_<OP>) noexcept
  {
    return (OP == Matrix_Unary_Op_Enum::Transpose or OP == Matrix_Unary_Op_Enum::TransConj) ? true
                                                                                            : false;
  }

  ////////////////////////////////////
  // _matrix_unary_op_t_ arithmetic //
  ////////////////////////////////////
  //
  // By example:
  //
  // _identity_ <= transpose(_transpose_)
  //
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>) noexcept
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>) noexcept
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>) noexcept
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>) noexcept
  {
    return {};
  }

  //----------------------------------------------------------------

  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>) noexcept
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>) noexcept
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>) noexcept
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>) noexcept
  {
    return {};
  }

  //----------------------------------------------------------------

  template <Matrix_Unary_Op_Enum OP>
  constexpr auto
  transconjugate(const _matrix_unary_op_t_<OP> op) noexcept
  {
    return conjugate(transpose(op));
  }

  ///////////////////////////////////////////
  // _matrix_unary_op_t_ action on scalars //
  ///////////////////////////////////////////
  //
  // By example: if z is complex
  //
  // z_bar = transform_scalar(_transconjugate_,z)
  //
  template <Matrix_Unary_Op_Enum OP, typename SCALAR>
  constexpr auto
  transform_scalar(const _matrix_unary_op_t_<OP>, const SCALAR& scalar) noexcept
  {
    return scalar;
  }

  template <Matrix_Unary_Op_Enum OP, typename SCALAR>
  constexpr auto
  transform_scalar(const _matrix_unary_op_t_<OP> op, const std::complex<SCALAR>& scalar) noexcept
  {
    if constexpr (op == _conjugate_ or op == _transConj_)
    {
      return std::conj(scalar);
    }

    return scalar;
  }

}  // namespace LinearAlgebra
