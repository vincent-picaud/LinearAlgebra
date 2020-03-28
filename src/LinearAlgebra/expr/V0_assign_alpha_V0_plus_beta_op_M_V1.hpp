//
// CAVEAT: in order to aExpr_Selector_Enum confusion between alpha, beta it is better to stick to blas conventions:
//
// v_0 = \alpha op(M) v_1 + \beta v_0
//

#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_scan.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/all_same_type.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

#include "LinearAlgebra/blas/blas.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  // \begin{equation*}
  // v_0 = \alpha v_0 + \beta op(M) v_1
  // \end{equation*}
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,    // Undefined implementation
         Vector_Crtp<V_0_TYPE>& v_0,                                     // v_0 =
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
         _matrix_unary_op_t_<M_OP> op,                                   // op
         const Matrix_Crtp<M_TYPE>& M,                                   // M
         const Vector_Crtp<V_1_TYPE>& v_1,                               // v_1
         _plus_t_,                                                       // +
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
         _vector_0_t_)                                                   // v_0
  {
    static_assert(not std::is_same_v<M_TYPE, M_TYPE>, "Not implemented");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  // \begin{equation*}
  // v_0 = \alpha v_0 + \beta op(M) v_1
  // \end{equation*}
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V_0_TYPE>& v_0,  // v_0 =
         // const typename V_0_TYPE::element_type alpha,
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
         _matrix_unary_op_t_<M_OP> op,                                   // op
         const Matrix_Crtp<M_TYPE>& M,                                   // M
         const Vector_Crtp<V_1_TYPE>& v_1,                               // v_1
         _plus_t_,                                                       // +
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
         _vector_0_t_)                                                   // v_0
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op, dimension_predicate(M)) * dimension_predicate(v_1) +
           dimension_predicate(v_0));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), v_0.impl(), alpha, op, M.impl(), v_1.impl(), _plus_, beta,
                  _vector_0_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  //
  // v_0 = \beta v_0 + \alpha op(M) v_1
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V_0_TYPE>& v_0,                                      // v_0 =
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE>& beta,   // β
         const _vector_0_t_,                                              // v_0,
         const _plus_t_,                                                  // +
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE>& alpha,  // α
         const _matrix_unary_op_t_<M_OP> op,                              // op
         const Matrix_Crtp<M_TYPE>& M,                                    // M
         const Vector_Crtp<V_1_TYPE>& v_1)                                // v_1
  {
    //assert(0);

    return assign(v_0, alpha, op, M, v_1, _plus_, beta, _vector_0_);
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  // TODO: the current implementation is concise, but far to be
  //       optimal concerning performance, in peculiar the number of
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
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,      // Generic implementation
         Dense_Vector_Crtp<V_0_TYPE>& v_0,                               // v_0 =
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
    assign(v_0, beta, _vector_0_);

    // alpha = 0 ? -> nothing to do
    //
    if (alpha == 0)
    {
      return Expr_Selector_Enum::Generic;
    }

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
        assign(v_0, _vector_0_, _plus_, alpha, v_1);
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
          assign(v_0, alpha, transpose(op), create_matrix_view_strict_upper_triangular(M), v_1,
                 _plus_, 1, _vector_0_);
        }
        else
        {
          assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

          assign(v_0, alpha, transpose(op), create_matrix_view_strict_lower_triangular(M), v_1,
                 _plus_, 1, _vector_0_);
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
          assign(v_0, alpha, transconjugate(op), create_matrix_view_strict_upper_triangular(M), v_1,
                 _plus_, 1, _vector_0_);
        }
        else
        {
          assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

          assign(v_0, alpha, transconjugate(op), create_matrix_view_strict_lower_triangular(M), v_1,
                 _plus_, 1, _vector_0_);
        }
      }
      break;

      default:
        throw "not implemented";
    }
    return selected;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<V_0_TYPE>& v_0,                               // v_0 =
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
         _matrix_unary_op_t_<M_OP> op,                                   // op
         const Dense_Matrix_Crtp<M_TYPE>& M,                             // M
         const Dense_Vector_Crtp<V_1_TYPE>& v_1,                         // v_1
         _plus_t_,                                                       // +
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
         _vector_0_t_)                                                   // v_0
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<M_OP> &&
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<M_TYPE>, Element_Type_t<V_0_TYPE>,
                              Element_Type_t<V_1_TYPE>> &&
              // Scalar support
              Is_CBlas_Supported_Scalar_v<Element_Type_t<M_TYPE>> &&
              // Generic matrix
              (M_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None),
          Expr_Selector_Enum>
  {
    Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<M_OP>, M.I_size(), M.J_size(), alpha,
               M.data(), M.leading_dimension(), v_1.data(), v_1.increment(), beta, v_0.data(),
               v_0.increment());
    return selected;
  }
#endif
}
