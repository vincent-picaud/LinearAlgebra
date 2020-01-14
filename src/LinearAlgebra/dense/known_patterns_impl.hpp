#pragma once

#include "LinearAlgebra/dense/known_patterns.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

namespace LinearAlgebra
{
  //****************************************************************
  // v = alpha
  //****************************************************************
  //
  // An example to show how to:
  // - provide a generic implementation
  // - a blas wrapping (to do)
  // - a static size implementation
  //
  // It works as follows:
  //
  // We first check for static size, if size are static here we call
  // generic implementation (that will unroll loops).
  //
  // If the vector has no static size, the Blas subroutine will be
  // called (if element_type is ok). Otherwise the fall back is again
  // the generic implementation.
  //
  template <typename V_TYPE>
  void expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
            Default_Vector_Crtp<V_TYPE>& v,                     // v
            _assign_t_,                                         // =
            const typename V_TYPE::element_type scalar)         // scalar

  {
    v.map([scalar](auto& v_i) { v_i = scalar; });
  }

  //
  // TODO: Blas wrapping with const Expr_Selector<Expr_Selector_Enum::Blas>
  //

  template <typename V_0_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Static>&,  // Static implementation
       Default_Vector_Crtp<V_0_TYPE>& v,                  // v
       _assign_t_,                                        // =
       const typename V_0_TYPE::element_type scalar       // scalar
       )
      //  SFINAE restricts to static size
      -> std::enable_if_t<Is_Std_Integral_Constant_Of_Type_v<size_t, typename V_0_TYPE::size_type>>
  {
    expr(Expr_Selector<Expr_Selector_Enum::Generic>(), v, _assign_, scalar);
  }
  //
  // Matrix version
  //
  template <typename M_0_TYPE>
  void expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
            Default_Matrix_Crtp<M_0_TYPE>& M_0,                 // matrix_0
            _assign_t_,                                         // =
            const typename M_0_TYPE::element_type scalar)       // scalar
  {
    static_assert(Default_Matrix_Crtp<M_0_TYPE>::matrix_special_structure_type::value !=
                  Matrix_Special_Structure_Enum::Unit_Triangular);

    M_0.map([scalar](auto& m_ij) { m_ij = scalar; });
  }

  //****************************************************************
  // v_0 = alpha v_0 (Blas's scal)
  //****************************************************************
  //
  template <typename V_0_TYPE>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Default_Vector_Crtp<V_0_TYPE>& v_0,                 // vector_0
       _assign_t_,                                         // =
       const typename V_0_TYPE::element_type scalar,       // scalar
       _vector_0_t_                                        // vector_0
  )
  {
    if (scalar == 0)
    {
      return expr(v_0, _assign_, 0);
    }

    if (scalar == 1)
    {
      return;
    }

    if (scalar == -1)
    {
      v_0.map([](auto& v_0_i) { v_0_i = -v_0_i; });
      return;
    }

    v_0.map([scalar](auto& v_0_i) { v_0_i *= scalar; });
  }
  //
  // Matrix version
  //
  template <typename M_0_TYPE>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Default_Matrix_Crtp<M_0_TYPE>& m_0,                 // matrix_0
       _assign_t_,                                         // =
       const typename M_0_TYPE::element_type scalar,       // scalar
       _matrix_0_t_                                        // matrix_0
  )
  {
    static_assert(Default_Matrix_Crtp<M_0_TYPE>::matrix_special_structure_type::value !=
                  Matrix_Special_Structure_Enum::Unit_Triangular);
    //
    // TODO check Hermitian: only real coef (otherwise diagonal is no
    //      more real)

    if (scalar == 0)
    {
      return expr(m_0, _assign_, 0);
    }

    if (scalar == 1)
    {
      return;
    }

    if (scalar == -1)
    {
      m_0.map([](auto& v_0_i) { v_0_i = -v_0_i; });
      return;
    }

    m_0.map([scalar](auto& v_0_i) { v_0_i *= scalar; });
  }
  //****************************************************************
  // v_0 = v_0 + alpha v_1 (Blas's axpy)
  //****************************************************************
  //
  template <typename V_0, typename V_1>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Default_Vector_Crtp<V_0>& v_0,                      // vector_0
       _assign_t_,                                         // =
       _vector_0_t_,                                       // vector_0
       _plus_t_,                                           // +
       const typename V_1::element_type scalar,            // scalar
       const Default_Vector_Crtp<V_1>& v_1                 // vector_1
  )
  {
    assert(are_compatibles(v_0.storage_scheme(), v_1.storage_scheme()));

    if (scalar == 0) return;

    if ((void*)&v_0 == (void*)&v_1)
    {
      return expr(v_0, _assign_, 1 + scalar, _vector_0_);
    }

    if (scalar == 1)
    {
      return v_0.map_indexed([&v_1](auto& v_0_i, const size_t i) { v_0_i += v_1[i]; });
    }

    if (scalar == -1)
    {
      return v_0.map_indexed([&v_1](auto& v_0_i, const size_t i) { v_0_i -= v_1[i]; });
    }

    v_0.map_indexed([&v_1, scalar](auto& v_0_i, const size_t i) { v_0_i += scalar * v_1[i]; });
  }

  //****************************************************************
  // M_0 = α.M_0 + β.v_1 transpose v_1 (rank-one udpate, M_0 is symmetric)
  //****************************************************************
  //
  template <typename M_0_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Default_Matrix_Crtp<M_0_TYPE>& M_0,                 // matrix_0
       _assign_t_,                                         // =
       const typename M_0_TYPE::element_type alpha,        // alpha
       _matrix_0_t_,                                       // matrix_0
       _plus_t_,                                           // +
       const typename V_1_TYPE::element_type beta,         // beta
       Default_Vector_Crtp<V_1_TYPE>& v_1,                 // vector_1
       _transpose_t_,                                      // transpose
       _vector_1_t_                                        // vector_1
       ) -> std::enable_if_t<M_0_TYPE::matrix_special_structure_type::value ==
                             Matrix_Special_Structure_Enum::Symmetric>
  {
    expr(M_0, _assign_, alpha, _matrix_0_);

    M_0.map_indexed([beta, &v_1](auto& m_ij, const size_t i, const size_t j) {
      m_ij += beta * v_1[i] * v_1[j];
    });
  }

  //****************************************************************
  // v_0 = alpha.v_0 + beta.op(M).v_1
  //****************************************************************
  // - generic implementation (that also cover the static size case)
  // - TODO Blas
  //
  // TODO: the current implementation is very concise, but far to be
  //       optimal concerning FLOPs, in peculiar the number of
  //       products can be greatly reduced.
  //
  //       The origin of the problem is the systematic product by
  //       beta, that could be more efficiently done after the sums...
  //
  //       A possible "patch" is to create a temporary vector
  //       v_2=beta*v_1 and self call this routine with beta = 1
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Default_Vector_Crtp<V_0_TYPE>& v_0,                 // v_0
       _assign_t_,                                         // =
       const typename V_0_TYPE::element_type alpha,        // alpha
       _vector_0_t_,                                       // v_0
       _plus_t_,                                           // +
       const typename V_1_TYPE::element_type beta,         // beta
       _matrix_unary_op_t_<M_OP> op,                       // op
       const Default_Matrix_Crtp<M_TYPE>& M,               // M
       const Default_Vector_Crtp<V_1_TYPE>& v_1            // v_1
  )
  {
    assert((void*)&v_0 != (void*)&v_1);

    // v_0 = alpha.v_0
    //
    expr(v_0, _assign_, alpha, _vector_0_);

    // beta = 0 ? -> nothing to do
    //
    if (beta == 0) return;

    //
    // TODO:beta != 1 ? -> you can reduce products by v_2 = beta v_1 then recall with beta = 1
    //

    // expr: v_0 = v_0 + β.op(M).v_1 ( = v_0 + op(M).(β.v_1))
    //
    switch (M_TYPE::matrix_special_structure_type::value)
    {
      case Matrix_Special_Structure_Enum::Unit_Triangular:
        // Diagonal contribution: v_0 = v_0 + β.v_1
        //
        expr(v_0, _assign_, _vector_0_, _plus_, beta, v_1);
        //
        // no break here
        //
      case Matrix_Special_Structure_Enum::None:
      case Matrix_Special_Structure_Enum::Triangular_Strict:
      case Matrix_Special_Structure_Enum::Triangular:
      {
        if (op == _identity_ or op == _conjugate_)
        {
          M.map_indexed([&v_0, &v_1, op, beta](const auto m_ij, const size_t i, const size_t j) {
            v_0[i] += beta * transform_scalar(op, m_ij) * v_1[j];
          });
        }
        else
        {
          assert(op == _transpose_ or op == _transConj_);

          M.map_indexed([&v_0, &v_1, op, beta](const auto m_ij, const size_t i, const size_t j) {
            v_0[j] += beta * transform_scalar(op, m_ij) * v_1[i];
          });
        }
      }
      break;

      case Matrix_Special_Structure_Enum::Symmetric:
      {
        // invariant by transposition
        //
        M.map_indexed([&v_0, &v_1, op, beta](const auto m_ij, const size_t i, const size_t j) {
          v_0[i] += beta * transform_scalar(op, m_ij) * v_1[j];
        });

        // Missing part
        //
        assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper or
               M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

        if constexpr (M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper)
        {
          expr(v_0, _assign_, 1, _vector_0_, _plus_, beta, transpose(op),
               view_as_upper_triangular_strict(M), v_1);
        }
        else
        {
          assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

          expr(v_0, _assign_, 1, _vector_0_, _plus_, beta, transpose(op),
               view_as_lower_triangular_strict(M), v_1);
        }
      }
      break;

      case Matrix_Special_Structure_Enum::Hermitian:
      {
        // NOT invariant by transposition
        // - identity  -> identity
        // - transConj -> identity
        // - conjugate -> conjugate
        // - transpose -> conjugate
        //
        if constexpr (op == _identity_ or op == _transConj_)
        {
          M.map_indexed([&v_0, &v_1, beta](const auto m_ij, const size_t i, const size_t j) {
            v_0[i] += beta * m_ij * v_1[j];
          });
        }
        else
        {
          assert(op == _transpose_ or op == _conjugate_);

          M.map_indexed([&v_0, &v_1, beta](const auto m_ij, const size_t i, const size_t j) {
            v_0[i] += beta * transform_scalar(_conjugate_, m_ij) * v_1[j];
          });
        }

        // Missing part
        //
        assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper or
               M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

        if constexpr (M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper)
        {
          expr(v_0, _assign_, 1, _vector_0_, _plus_, beta, transconjugate(op),
               view_as_upper_triangular_strict(M), v_1);
        }
        else
        {
          assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

          expr(v_0, _assign_, 1, _vector_0_, _plus_, beta, transconjugate(op),
               view_as_lower_triangular_strict(M), v_1);
        }
      }
      break;

      default:
        throw "not implemented";
    }
  }
}
