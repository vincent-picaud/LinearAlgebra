//
// Generic for: V0 = α op(M) V1 + β VX
//
// CAVEAT: a lot TODO
// - put in reverse polish
// - debug routines (symmetric for sure is bugged)
#pragma once

#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V0_driver.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V2_driver.hpp"

#include "LinearAlgebra/dense/matrix_scan.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  // TODO: commented as buggy (at least for symmetric)
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
  // template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
  //           typename V_1_TYPE>
  // Expr_Selector_Enum
  // assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,      //
  //        Dense_Vector_Crtp<V_0_TYPE>& v_0,                               // v_0 =
  //        const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
  //        const _matrix_unary_op_t_<M_OP> op,                             // op
  //        const Dense_Matrix_Crtp<M_TYPE>& M,                             // M
  //        const Dense_Vector_Crtp<V_1_TYPE>& v_1,                         // v_1
  //        const _plus_t_,                                                 // +
  //        const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
  //        const _lhs_t_                                                   // v_0
  // )
  // {
  //   assert((void*)&v_0 != (void*)&v_1);

  //   // v_0 = beta.v_0
  //   //
  //   assign(v_0, beta, _lhs_);

  //   // alpha = 0 ? -> nothing to do
  //   //
  //   if (alpha == 0)
  //   {
  //     return Expr_Selector_Enum::Generic;
  //   }

  //   //
  //   // TODO:alpha != 1 ? -> you can reduce products by v_2 = alpha v_1 then recall with alpha = 1
  //   //

  //   // expr: v_0 = v_0 + β.op(M).v_1 ( = v_0 + op(M).(β.v_1))
  //   //
  //   switch (M_TYPE::matrix_special_structure_type::value)
  //   {
  //     case Matrix_Special_Structure_Enum::Unit_Triangular:
  //       // Diagonal contribution: v_0 = v_0 + β.v_1
  //       //
  //       assign(v_0, _lhs_, _plus_, alpha, v_1);
  //       //
  //       // no break here
  //       //
  //     case Matrix_Special_Structure_Enum::None:
  //     case Matrix_Special_Structure_Enum::Triangular_Strict:
  //     case Matrix_Special_Structure_Enum::Triangular:
  //     {
  //       if (op == _identity_ or op == _conjugate_)
  //       {
  //         scan_indexed(
  //             [&v_0, &v_1, op, alpha](const size_t i, const size_t j, const auto m_ij) {
  //               v_0[i] += alpha * transform_scalar(op, m_ij) * v_1[j];
  //             },
  //             M);
  //       }
  //       else
  //       {
  //         assert(op == _transpose_ or op == _transConj_);

  //         scan_indexed(
  //             [&v_0, &v_1, op, alpha](const size_t i, const size_t j, const auto m_ij) {
  //               v_0[j] += alpha * transform_scalar(op, m_ij) * v_1[i];
  //             },
  //             M);
  //       }
  //     }
  //     break;

  //     case Matrix_Special_Structure_Enum::Symmetric:
  //     {
  //       // invariant by transposition
  //       //
  //       scan_indexed(
  //           [&v_0, &v_1, op, alpha](const size_t i, const size_t j, const auto m_ij) {
  //             v_0[i] += alpha * transform_scalar(op, m_ij) * v_1[j];
  //           },
  //           M);

  //       // Missing part
  //       //
  //       assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper or
  //              M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

  //       if constexpr (M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper)
  //       {
  //         assign(v_0, alpha, transpose(op), create_matrix_view_strict_upper_triangular(M), v_1,
  //                _plus_, 1, _lhs_);
  //       }
  //       else
  //       {
  //         assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

  //         assign(v_0, alpha, transpose(op), create_matrix_view_strict_lower_triangular(M), v_1,
  //                _plus_, 1, _lhs_);
  //       }
  //     }
  //     break;

  //     case Matrix_Special_Structure_Enum::Hermitian:
  //     {
  //       // NOT invariant by transposition
  //       // - identity  -> identity
  //       // - transConj -> identity
  //       // - conjugate -> conjugate
  //       // - transpose -> conjugate
  //       //
  //       if constexpr (op == _identity_ or op == _transConj_)
  //       {
  //         scan_indexed([&v_0, &v_1, alpha](const size_t i, const size_t j,
  //                                          const auto m_ij) { v_0[i] += alpha * m_ij * v_1[j]; },
  //                      M);
  //       }
  //       else
  //       {
  //         assert(op == _transpose_ or op == _conjugate_);

  //         scan_indexed(
  //             [&v_0, &v_1, alpha](const size_t i, const size_t j, const auto m_ij) {
  //               v_0[i] += alpha * transform_scalar(_conjugate_, m_ij) * v_1[j];
  //             },
  //             M);
  //       }

  //       // Missing part
  //       //
  //       assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper or
  //              M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

  //       if constexpr (M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Upper)
  //       {
  //         assign(v_0, alpha, transconjugate(op), create_matrix_view_strict_upper_triangular(M), v_1,
  //                _plus_, 1, _lhs_);
  //       }
  //       else
  //       {
  //         assert(M_TYPE::matrix_storage_mask_type::value == Matrix_Storage_Mask_Enum::Lower);

  //         assign(v_0, alpha, transconjugate(op), create_matrix_view_strict_lower_triangular(M), v_1,
  //                _plus_, 1, _lhs_);
  //       }
  //     }
  //     break;

  //     default:
  //       throw "not implemented";
  //   }
  //   return selected;
  // }

  // template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V_1_TYPE,
  //           typename V_2_TYPE>
  // Expr_Selector_Enum
  // assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,      //
  //        Dense_Vector_Crtp<V_0_TYPE>& v_0,                               // v_0 =
  //        const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
  //        const _matrix_unary_op_t_<M_OP> op,                             // op
  //        const Dense_Matrix_Crtp<M_TYPE>& M,                             // M
  //        const Dense_Vector_Crtp<V_1_TYPE>& v_1,                         // v_1
  //        const _plus_t_,                                                 // +
  //        const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
  //        const Dense_Vector_Crtp<V_2_TYPE>& v_2                          // v_2
  // )
  // {
  //   v_0 = v_2;
  //   return assign(v_0, alpha, op, M, v_1, _plus_, beta, _lhs_);
  // }
}
