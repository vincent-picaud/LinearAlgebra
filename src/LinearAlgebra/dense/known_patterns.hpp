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

#pragma once

#include <ccomplex>
#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"

namespace KissDStream
{
  // Tags definitions
  //
  // Note: as we do not use *capitalized first letter* these are
  // *legal* C++ identifiers, see
  // https://en.cppreference.com/w/cpp/language/identifiers
  //
  struct _plus_t_
  {
  };
  constexpr auto _plus_ = _plus_t_();

  struct _assign_t_
  {
  };
  constexpr auto _assign_ = _assign_t_();

  //================================================================

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

  //================================================================

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
  operator==(const _matrix_unary_op_t_<OP_A>, const _matrix_unary_op_t_<OP_B>)
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

  //----------------------------------------------------------------

  template <Matrix_Unary_Op_Enum OP>
  constexpr bool
  does_it_transpose_matrix_dimension(const _matrix_unary_op_t_<OP>)
  {
    return (OP == Matrix_Unary_Op_Enum::Transpose or OP == Matrix_Unary_Op_Enum::TransConj) ? true
                                                                                            : false;
  }

  //----------------------------------------------------------------

  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>)
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>)
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>)
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>
  transpose(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>)
  {
    return {};
  }

  //----------------------------------------------------------------

  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>)
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>)
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::TransConj>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Transpose>)
  {
    return {};
  }
  constexpr _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Conjugate>
  conjugate(const _matrix_unary_op_t_<Matrix_Unary_Op_Enum::Identity>)
  {
    return {};
  }

  //----------------------------------------------------------------

  template <Matrix_Unary_Op_Enum OP>
  constexpr auto
  transconjugate(const _matrix_unary_op_t_<OP> op)
  {
    return conjugate(transpose(op));
  }

  //----------------------------------------------------------------

  template <Matrix_Unary_Op_Enum OP, typename SCALAR>
  auto
  transform_scalar(const _matrix_unary_op_t_<OP>, const SCALAR& scalar)
  {
    return scalar;
  }

  template <Matrix_Unary_Op_Enum OP, typename SCALAR>
  auto
  transform_scalar(const _matrix_unary_op_t_<OP> op, const std::complex<SCALAR>& scalar)
  {
    if constexpr (op == _conjugate_ or op == _transConj_)
    {
      return std::conj(scalar);
    }

    return scalar;
  }

  //****************************************************************

  enum class Expr_Order_Enum : int
  {
    Undefined,
    Generic,
    Blas,
    Static,
    END
  };

  template <Expr_Order_Enum EXPR_ORDER = Expr_Order_Enum::END>
  struct Expr_Order : Expr_Order<static_cast<Expr_Order_Enum>(
                          static_cast<std::underlying_type_t<Expr_Order_Enum>>(EXPR_ORDER) - 1)>
  {
  };
  template <>
  struct Expr_Order<Expr_Order_Enum::Undefined>
  {
  };

  //****************************************************************
  // v_0 = alpha.v_0 + beta.op(M).v_1 (Blas's gemv, trmv, symv etc...)
  //****************************************************************
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  void expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
            Vector_Crtp<V_0_TYPE>& v_0,                     // v_0
            _assign_t_,                                     // =
            const typename V_0_TYPE::element_type alpha,    // alpha
            _vector_0_t_,                                   // v_0
            _plus_t_,                                       // +
            const typename V_1_TYPE::element_type beta,     // beta
            _matrix_unary_op_t_<M_OP> op,                   // op
            const Matrix_Crtp<M_TYPE>& M,                   // M
            const Vector_Crtp<V_1_TYPE>& v_1)               // v_1
  {
    static_assert(not std::is_same_v<M, M>, "Not implemented");
  }

  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  void expr(Vector_Crtp<V_0_TYPE>& v_0,                   // v_0
            _assign_t_,                                   // =
            const typename V_0_TYPE::element_type alpha,  // alpha
            _vector_0_t_,                                 // v_0
            _plus_t_,                                     // +
            const typename V_1_TYPE::element_type beta,   // beta
            _matrix_unary_op_t_<M_OP> op,                 // op
            const Matrix_Crtp<M_TYPE>& M,                 // M
            const Vector_Crtp<V_1_TYPE>& v_1)             // v_1
  {
    // Here is the right place to check dimension once for all.
    //
    assert(v_0.size() == (does_it_transpose_matrix_dimension(op) ? M.J_size() : M.I_size()));
    assert(v_1.size() == (does_it_transpose_matrix_dimension(op) ? M.I_size() : M.J_size()));

    // Delegate computation
    expr(Expr_Order<>(), v_0.impl(), _assign_, alpha, _vector_0_, _plus_, beta, op, M.impl(),
         v_1.impl());
  }

  //****************************************************************
  // v_0 = alpha
  //****************************************************************
  //

  template <typename V>
  void expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
            Vector_Crtp<V>& v_0,                            // vector_0
            _assign_t_,                                     // =
            const typename V::element_type scalar)          // scalar
  {
    static_assert(not(std::is_same_v<V, V>), "Undefined implementation");
  }

  template <typename V>
  void expr(Vector_Crtp<V>& v_0,                    // vector_0
            _assign_t_,                             // =
            const typename V::element_type scalar)  // scalar
  {
    expr(Expr_Order<>(), v_0.impl(), _assign_, scalar);
  }

  //****************************************************************
  // M_0 = alpha
  //****************************************************************
  //

  template <typename M>
  void expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
            Matrix_Crtp<M>& M_0,                            // matrix_0
            _assign_t_,                                     // =
            const typename M::element_type scalar)          // scalar
  {
    static_assert(not(std::is_same_v<M, M>), "Undefined implementation");
  }

  template <typename M>
  void expr(Matrix_Crtp<M>& M_0,                    // matrix_0
            _assign_t_,                             // =
            const typename M::element_type scalar)  // scalar
  {
    expr(Expr_Order<>(), M_0.impl(), _assign_, scalar);
  }
  //****************************************************************
  // v_0 = alpha v_0 (Blas's scal)
  //****************************************************************
  //
  template <typename V_0_TYPE>
  void
  expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
       Vector_Crtp<V_0_TYPE>& v_0,                     // vector_0
       _assign_t_,                                     // =
       const typename V_0_TYPE::element_type scalar,   // scalar
       _vector_0_t_                                    // vector_0
  )
  {
    static_assert(not(std::is_same_v<V_0_TYPE, V_0_TYPE>), "Undefined implementation");
  }

  template <typename V_0_TYPE>
  void
  expr(Vector_Crtp<V_0_TYPE>& v_0,                    // vector_0
       _assign_t_,                                    // =
       const typename V_0_TYPE::element_type scalar,  // scalar
       _vector_0_t_                                   // vector_0
  )
  {
    expr(Expr_Order<>(), v_0.impl(), _assign_, scalar, _vector_0_);
  }
  //
  // Matrix version
  //
  template <typename M_0_TYPE>
  void
  expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
       Matrix_Crtp<M_0_TYPE>& M_0,                     // matrix_0
       _assign_t_,                                     // =
       const typename M_0_TYPE::element_type scalar,   // scalar
       _matrix_0_t_                                    // matrix_0
  )
  {
    static_assert(not(std::is_same_v<M_0_TYPE, M_0_TYPE>), "Undefined implementation");
  }

  template <typename M_0_TYPE>
  void
  expr(Matrix_Crtp<M_0_TYPE>& M_0,                    // matrix_0
       _assign_t_,                                    // =
       const typename M_0_TYPE::element_type scalar,  // scalar
       _matrix_0_t_                                   // matrix_0
  )
  {
    expr(Expr_Order<>(), M_0.impl(), _assign_, scalar, _matrix_0_);
  }
  //****************************************************************
  // M_0 = α.M_0 + β.v_1 transpose v_1 (rank-one udpate, M_0 is symmetric)
  //****************************************************************
  //
  template <typename M_0_TYPE, typename V_1_TYPE>
  void
  expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
       Matrix_Crtp<M_0_TYPE>& M_0,                     // matrix_0
       _assign_t_,                                     // =
       const typename M_0_TYPE::element_type alpha,    // alpha
       _matrix_0_t_,                                   // matrix_0
       _plus_t_,                                       // +
       const typename V_1_TYPE::element_type beta,     // beta
       Vector_Crtp<V_1_TYPE>& v_1,                     // vector_1
       _transpose_t_,                                  // transpose
       _vector_1_t_                                    // vector_1
  )
  {
    static_assert(not(std::is_same_v<M_0_TYPE, M_0_TYPE>), "Undefined implementation");
  }

  template <typename M_0_TYPE, typename V_1_TYPE>
  void
  expr(Matrix_Crtp<M_0_TYPE>& M_0,                   // matrix_0
       _assign_t_,                                   // =
       const typename M_0_TYPE::element_type alpha,  // alpha
       _matrix_0_t_,                                 // matrix_0
       _plus_t_,                                     // +
       const typename V_1_TYPE::element_type beta,   // beta
       Vector_Crtp<V_1_TYPE>& v_1,                   // vector_1
       _transpose_t_,                                // transpose
       _vector_1_t_                                  // vector_1
  )
  {
    assert(M_0.I_size() == M_0.J_size());
    assert(M_0.I_size() == v_1.size());

    expr(Expr_Order<>(), M_0.impl(), _assign_, alpha, _matrix_0_, _plus_, beta, v_1.impl(),
         _transpose_, _vector_1_);
  }

  //****************************************************************
  // v_0 = v_0 + alpha v_1 (Blas's axpy)
  //****************************************************************
  //

  template <typename V_0, typename V_1>
  void
  expr(const Expr_Order<Expr_Order_Enum::Undefined>&,  // Undefined implementation
       Vector_Crtp<V_0>& v_0,                          // vector_0
       _assign_t_,                                     // =
       _vector_0_t_,                                   // vector_0
       _plus_t_,                                       // +
       const typename V_1::element_type scalar,        // scalar
       const Vector_Crtp<V_1>& v_1                     // vector_1
  )
  {
    static_assert(not(std::is_same_v<V_0, V_0>), "Undefined implementation");
  }

  template <typename V_0, typename V_1>
  void
  expr(Vector_Crtp<V_0>& v_0,                    // vector_0
       _assign_t_,                               // =
       _vector_0_t_,                             // vector_0
       _plus_t_,                                 // +
       const typename V_1::element_type scalar,  // scalar
       const Vector_Crtp<V_1>& v_1               // vector_1
  )
  {
    assert(v_0.size() == v_1.size());

    expr(Expr_Order<>(), v_0.impl(), _assign_, _vector_0_, _plus_, scalar, v_1.impl());
  }

}
