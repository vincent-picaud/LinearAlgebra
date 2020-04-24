//
// Blas routines for
//
//   V0 = α op(M) V1
//
// CEVEAT: like it is nearly the same we also take into account:
//
//   V0 = α op( inverse (M) ) V1
//
#pragma once

#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"

#include "LinearAlgebra/expr/X_eq_aX_vector.hpp"

#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V0_driver.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_driver.hpp"

#include "LinearAlgebra/utils/all_same_type.hpp"

#include "LinearAlgebra/blas/blas.hpp"

#if (HAS_BLAS)

namespace LinearAlgebra
{
  //================================================================
  // CAVEAT: redirect matrices that are NOT TRIANGULAR to the more
  //         general V0=αop(M)V1+βVX
  // Note: note sure that really a good idea.... <- this is BAD idea: to remove
  // ================================================================
  //
  //
  // vector0 = alpha * transpose(M1) * vector1
  // vector0 = * * alpha op1 matrix1 vector1
  //
  template <typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
          // Same scalar everywhere
          All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>,
                          Element_Type_t<VECTOR0_IMPL>,
                          Element_Type_t<VECTOR1_IMPL>> &&
          // Scalar support
          Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
          // *NOT* Triangular Matrix
          !Blas::Support_CBlas_Diag_v<MATRIX1_IMPL>>

  {
    // redirect
    assign(selected,
           vector0,
           _plus_,
           _product_,
           _product_,
           alpha.impl(),
           op1,
           matrix1,
           vector1,
           _product_,
           ALPHA_IMPL(0),
           _lhs_);

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////

  //================================================================
  // trmv
  //================================================================
  //
  //
  // VECTOR0 = alpha * transpose(M1) * VECTOR0
  // vector0 = * * alpha op1 matrix1 vector0
  //
  template <typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,  // Undefined implementation
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _lhs_t_)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
          // Same scalar everywhere
          All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>, Element_Type_t<VECTOR0_IMPL>> &&
          // Scalar support
          Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
          // Triangular Matrix
          Blas::Support_CBlas_Diag_v<MATRIX1_IMPL>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case
    assert(are_not_aliased_p(vector0, matrix1));

    assign(vector0, _product_, alpha.impl(), _lhs_);

    Blas::trmv(CblasColMajor,
               Blas::To_CBlas_UpLo_v<MATRIX1_IMPL>,
               Blas::To_CBlas_Transpose_v<OP1_ENUM>,
               Blas::To_CBlas_Diag_v<MATRIX1_IMPL>,
               matrix1.I_size(),
               matrix1.data(),
               matrix1.leading_dimension(),
               vector0.data(),
               vector0.increment());

    DEBUG_SET_SELECTED(selected);
  }
  //
  // vector0 = alpha * transpose(M1) * vector1
  // vector0 = * * alpha op1 matrix1 vector1
  //
  template <typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
          // Same scalar everywhere
          All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>,
                          Element_Type_t<VECTOR0_IMPL>,
                          Element_Type_t<VECTOR1_IMPL>> &&
          // Scalar support
          Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
          // Triangular Matrix
          Blas::Support_CBlas_Diag_v<MATRIX1_IMPL>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case

    assign(vector0, _product_, alpha.impl(), vector1);
    assign(selected, vector0, _product_, _product_, ALPHA_IMPL(1), op1, matrix1, _lhs_);

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  // trsv
  //================================================================
  //
  //
  // VECTOR0 = alpha * transpose(inverse(M1)) * VECTOR0
  // vector0 = * * alpha op1 inverse matrix1 vector0
  //
  template <typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const _inverse_t_,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _lhs_t_)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
          // Same scalar everywhere
          All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>, Element_Type_t<VECTOR0_IMPL>> &&
          // Scalar support
          Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
          // Triangular Matrix
          Blas::Support_CBlas_Diag_v<MATRIX1_IMPL>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case
    assert(are_not_aliased_p(vector0, matrix1));

    assign(vector0, _product_, alpha.impl(), _lhs_);

    Blas::trsv(CblasColMajor,
               Blas::To_CBlas_UpLo_v<MATRIX1_IMPL>,
               Blas::To_CBlas_Transpose_v<OP1_ENUM>,
               Blas::To_CBlas_Diag_v<MATRIX1_IMPL>,
               matrix1.I_size(),
               matrix1.data(),
               matrix1.leading_dimension(),
               vector0.data(),
               vector0.increment());

    DEBUG_SET_SELECTED(selected);
  }
  //
  // vector0 = alpha * transpose(inverse(M1)) * vector1
  // vector0 = * * alpha op1 inverse matrix1 vector1
  //
  template <typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,  // Undefined implementation
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const _inverse_t_,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
          // Same scalar everywhere
          All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>,
                          Element_Type_t<VECTOR0_IMPL>,
                          Element_Type_t<VECTOR1_IMPL>> &&
          // Scalar support
          Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
          // Triangular Matrix
          Blas::Support_CBlas_Diag_v<MATRIX1_IMPL>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case

    assign(vector0, _product_, alpha.impl(), vector1);
    assign(selected, vector0, _product_, _product_, ALPHA_IMPL(1), op1, _inverse_, matrix1, _lhs_);

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra

#endif
