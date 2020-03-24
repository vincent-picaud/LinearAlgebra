//
// Notations:
//
// arg_0 = arg_1 op arg_2....
//
// arg_0 is ALWAYS the LHS
// arg_i, i>0belo,g the the RHS, i denotes the rank of the first occurrence
//
// Example: $M_0=v_1.v_1^t$ is translated into
//
// M_0 = v_1 _transpose_ _vector_1_
//
// Product is not noted.
//
// However, please note that special products like (_cwise_product_,
// _Kronecker_product_) are *noted*.
//
#pragma once

#include <ccomplex>

namespace LinearAlgebra
{
  ///////////////////////////////////////////////////////
  // Tags used to notify operations (plus, product...) //
  ///////////////////////////////////////////////////////
  //
  // Note: as we do not use *capitalized first letter* these are
  // *legal* C++ identifiers, see
  // https://en.cppreference.com/w/cpp/language/identifiers
  //
  struct _plus_t_
  {
  };
  constexpr auto _plus_ = _plus_t_();

  struct _product_t_
  {
  };
  constexpr auto _product_ = _product_t_();

  struct _assign_t_
  {
  };
  constexpr auto _assign_ = _assign_t_();

  //////////////////////////////////
  // Tags used to notify argument //
  //////////////////////////////////
  //
  // By example:
  //
  // expr(v,_assign_,2.,_product_,_vector_0_)
  //
  // then _vector_0_ refers to the first (=0) vector argument, here v.
  //
  // The expression expr must be read as:
  //
  // v = 2 * v
  //
  struct _vector_0_t_
  {
  };
  struct _vector_1_t_
  {
  };
  struct _vector_2_t_
  {
  };
  constexpr auto _vector_0_ = _vector_0_t_();
  constexpr auto _vector_1_ = _vector_1_t_();
  constexpr auto _vector_2_ = _vector_2_t_();

  //================================================================

  struct _matrix_0_t_
  {
  };
  struct _matrix_1_t_
  {
  };
  struct _matrix_2_t_
  {
  };
  constexpr auto _matrix_0_ = _matrix_0_t_();
  constexpr auto _matrix_1_ = _matrix_1_t_();
  constexpr auto _matrix_2_ = _matrix_2_t_();

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
  struct _matrix_unary_op_t_
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

}
