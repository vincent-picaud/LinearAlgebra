#pragma once

#include "LinearAlgebra/expr/M_eq_aMM_bM/M0_eq_aM1M2_bM3_interface.hpp"
#include "LinearAlgebra/expr/copy_matrix.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/blas/subroutines_dense.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"
#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

#if (HAS_BLAS)

namespace LinearAlgebra
{
  ////// syrk ////
  //
  // M0 := α.M1.M1^t + β.M0
  //
  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            typename MATRIX0_IMPL,
            typename MATRIX1_IMPL,
            typename MATRIX2_IMPL,
            typename MATRIX3_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas>& selected,
         Dense_Matrix_Crtp<MATRIX0_IMPL>& matrix0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _identity_t_,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _transpose_t_,
         const Dense_Matrix_Crtp<MATRIX2_IMPL>& matrix2,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Dense_Matrix_Crtp<MATRIX3_IMPL>& matrix3)
      -> std::enable_if_t<
          Is_Symmetric_Matrix_v<MATRIX0_IMPL> and Is_Symmetric_Matrix_v<MATRIX3_IMPL> and
          Is_Full_Matrix_v<MATRIX1_IMPL> and Is_Full_Matrix_v<MATRIX2_IMPL> and
          Always_True_v<decltype(assign(matrix0, matrix3))> and
          Always_True_v<decltype(Blas::syrk_AAt(alpha.value(), matrix1, beta.value(), matrix0))>>

  {
    assert(same_mathematical_object_p(matrix1.impl(), matrix2.impl()));

    if (not same_mathematical_object_p(matrix0.impl(), matrix3.impl()))
    {
      assign(matrix0, matrix3);
    }

    Blas::syrk_AAt(alpha.value(), matrix1, beta.value(), matrix0);

    DEBUG_SET_SELECTED(selected);
  }

  ////// syrk ////
  //
  // M0 := α.M1^t.M1 + β.M0
  //
  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            typename MATRIX0_IMPL,
            typename MATRIX1_IMPL,
            typename MATRIX2_IMPL,
            typename MATRIX3_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas>& selected,
         Dense_Matrix_Crtp<MATRIX0_IMPL>& matrix0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _transpose_t_,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _identity_t_,
         const Dense_Matrix_Crtp<MATRIX2_IMPL>& matrix2,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Dense_Matrix_Crtp<MATRIX3_IMPL>& matrix3)
      -> std::enable_if_t<
          Is_Symmetric_Matrix_v<MATRIX0_IMPL> and Is_Symmetric_Matrix_v<MATRIX3_IMPL> and
          Is_Full_Matrix_v<MATRIX1_IMPL> and Is_Full_Matrix_v<MATRIX2_IMPL> and
          Always_True_v<decltype(assign(matrix0, matrix3))> and
          Always_True_v<decltype(Blas::syrk_AtA(alpha.value(), matrix1, beta.value(), matrix0))>>

  {
    assert(same_mathematical_object_p(matrix1.impl(), matrix2.impl()));

    if (not same_mathematical_object_p(matrix0.impl(), matrix3.impl()))
    {
      assign(matrix0, matrix3);
    }

    Blas::syrk_AtA(alpha.value(), matrix1, beta.value(), matrix0);

    DEBUG_SET_SELECTED(selected);
  }

  ////// gemm ////
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM,
            Matrix_Unary_Op_Enum OP2_ENUM,
            typename ALPHA_IMPL,
            typename BETA_IMPL,
            typename MATRIX0_IMPL,
            typename MATRIX1_IMPL,
            typename MATRIX2_IMPL,
            typename MATRIX3_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas>& selected,
         Dense_Matrix_Crtp<MATRIX0_IMPL>& matrix0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _matrix_unary_op_t_<OP2_ENUM> op2,
         const Dense_Matrix_Crtp<MATRIX2_IMPL>& matrix2,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Dense_Matrix_Crtp<MATRIX3_IMPL>& matrix3)
      -> std::enable_if_t<Is_Full_Matrix_v<MATRIX0_IMPL> and Is_Full_Matrix_v<MATRIX3_IMPL> and
                          Is_Full_Matrix_v<MATRIX1_IMPL> and Is_Full_Matrix_v<MATRIX2_IMPL> and
                          Always_True_v<decltype(assign(matrix0, matrix3))> and
                          Always_True_v<decltype(Blas::gemm(
                              alpha.value(), op1, matrix1, op2, matrix2, beta.value(), matrix0))>>

  {
    if (not same_mathematical_object_p(matrix0.impl(), matrix3.impl()))
    {
      assign(matrix0, matrix3);
    }

    Blas::gemm(alpha.value(), op1, matrix1, op2, matrix2, beta.value(), matrix0);

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra

#endif  // HAS_BLAS
