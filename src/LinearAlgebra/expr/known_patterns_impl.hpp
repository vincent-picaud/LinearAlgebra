#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/dense/matrix_map.hpp"
#include "LinearAlgebra/dense/matrix_scan.hpp"
#include "LinearAlgebra/dense/matrix_transform.hpp"

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/dense/vector_map.hpp"
#include "LinearAlgebra/dense/vector_transform.hpp"

#include "LinearAlgebra/expr/known_patterns.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //****************************************************************
  // v_0 = v_0 + alpha v_1 (Blas's axpy)
  //****************************************************************
  //
  template <typename V_0, typename V_1>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Vector_Crtp<V_0>& v_0,                        // vector_0
       _assign_t_,                                         // =
       _vector_0_t_,                                       // vector_0
       _plus_t_,                                           // +
       const typename V_1::element_type scalar,            // scalar
       const Dense_Vector_Crtp<V_1>& v_1                   // vector_1
  )
  {
    assert(are_compatible_p(v_0.storage_scheme(), v_1.storage_scheme()));

    if (scalar == 0) return;

    if ((void*)&v_0 == (void*)&v_1)
    {
      /*      return*/ expr(v_0, _assign_, 1 + scalar, _vector_0_);
    }

    if (scalar == 1)
    {
      transform([](const auto v0_i, const auto v1_i) { return v0_i + v1_i; }, v_0, v_1);
    }

    if (scalar == -1)
    {
      transform([](const auto v0_i, const auto v1_i) { return v0_i - v1_i; }, v_0, v_1);
    }

    transform([scalar](const auto v0_i, const auto v1_i) { return v0_i + scalar * v1_i; }, v_0,
              v_1);
  }

  //****************************************************************
  // M_0 = α.M_0 + β.v_1 transpose v_1 (rank-one udpate, M_0 is symmetric)
  //****************************************************************
  //
  template <typename M_0_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Matrix_Crtp<M_0_TYPE>& M_0,                   // matrix_0
       _assign_t_,                                         // =
       const typename M_0_TYPE::element_type alpha,        // alpha
       _matrix_0_t_,                                       // matrix_0
       _plus_t_,                                           // +
       const typename V_1_TYPE::element_type beta,         // beta
       Dense_Vector_Crtp<V_1_TYPE>& v_1,                   // vector_1
       _transpose_t_,                                      // transpose
       _vector_1_t_                                        // vector_1
       ) -> std::enable_if_t<M_0_TYPE::matrix_special_structure_type::value ==
                             Matrix_Special_Structure_Enum::Symmetric>
  {
    expr(M_0, _assign_, alpha, _matrix_0_);

    transform_indexed([beta, &v_1](const size_t i, const size_t j,
                                   const auto m_ij) { return m_ij + beta * v_1[i] * v_1[j]; },
                      M_0);
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
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,              // Generic implementation
       Dense_Vector_Crtp<V_0_TYPE>& v_0,                               // v_0
       _assign_t_,                                                     // =
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
       _matrix_unary_op_t_<M_OP> op,                                   // op
       const Dense_Matrix_Crtp<M_TYPE>& M,                             // M
       const Dense_Vector_Crtp<V_1_TYPE>& v_1,                         // v_1
       _plus_t_,                                                       // +
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
       _vector_0_t_                                                    // v_0
  )
  {
    assert((void*)&v_0 != (void*)&v_1);

    // v_0 = beta.v_0
    //
    expr(v_0, _assign_, beta, _vector_0_);

    // alpha = 0 ? -> nothing to do
    //
    if (alpha == 0) return;

    //
    // TODO:alpha != 1 ? -> you can reduce products by v_2 = alpha v_1 then recall with alpha = 1
    //

    // expr: v_0 = v_0 + β.op(M).v_1 ( = v_0 + op(M).(β.v_1))
    //
    switch (M_TYPE::matrix_special_structure_type::value)
    {
      case Matrix_Special_Structure_Enum::Unit_Triangular:
        // Diagonal contribution: v_0 = v_0 + β.v_1
        //
        expr(v_0, _assign_, _vector_0_, _plus_, alpha, v_1);
        //
        // no break here
        //
      case Matrix_Special_Structure_Enum::None:
      case Matrix_Special_Structure_Enum::Triangular_Strict:
      case Matrix_Special_Structure_Enum::Triangular:
      {
        if (op == _identity_ or op == _conjugate_)
        {
          scan_indexed(
              [&v_0, &v_1, op, alpha](const size_t i, const size_t j, const auto m_ij) {
                v_0[i] += alpha * transform_scalar(op, m_ij) * v_1[j];
              },
              M);
        }
        else
        {
          assert(op == _transpose_ or op == _transConj_);

          scan_indexed(
              [&v_0, &v_1, op, alpha](const size_t i, const size_t j, const auto m_ij) {
                v_0[j] += alpha * transform_scalar(op, m_ij) * v_1[i];
              },
              M);
        }
      }
      break;

      case Matrix_Special_Structure_Enum::Symmetric:
      {
        // invariant by transposition
        //
        scan_indexed(
            [&v_0, &v_1, op, alpha](const size_t i, const size_t j, const auto m_ij) {
              v_0[i] += alpha * transform_scalar(op, m_ij) * v_1[j];
            },
            M);

        // Missing part
        //
        assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper or
               M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

        if constexpr (M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper)
        {
          expr(v_0, _assign_, alpha, transpose(op), view_as_upper_triangular_strict(M), v_1, _plus_,
               1, _vector_0_);
        }
        else
        {
          assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

          expr(v_0, _assign_, alpha, transpose(op), view_as_lower_triangular_strict(M), v_1, _plus_,
               1, _vector_0_);
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
          scan_indexed([&v_0, &v_1, alpha](const size_t i, const size_t j,
                                           const auto m_ij) { v_0[i] += alpha * m_ij * v_1[j]; },
                       M);
        }
        else
        {
          assert(op == _transpose_ or op == _conjugate_);

          scan_indexed(
              [&v_0, &v_1, alpha](const size_t i, const size_t j, const auto m_ij) {
                v_0[i] += alpha * transform_scalar(_conjugate_, m_ij) * v_1[j];
              },
              M);
        }

        // Missing part
        //
        assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper or
               M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

        if constexpr (M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper)
        {
          expr(v_0, _assign_, alpha, transconjugate(op), view_as_upper_triangular_strict(M), v_1,
               _plus_, 1, _vector_0_);
        }
        else
        {
          assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

          expr(v_0, _assign_, alpha, transconjugate(op), view_as_lower_triangular_strict(M), v_1,
               _plus_, 1, _vector_0_);
        }
      }
      break;

      default:
        throw "not implemented";
    }
  }
}
