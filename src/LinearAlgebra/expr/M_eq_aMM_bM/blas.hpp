// [[file:blas.org]]
#if defined(HAS_BLAS)

#pragma once

#include "LinearAlgebra/expr/copy.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/blas/subroutines_dense.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"
#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

namespace LinearAlgebra
{
  // [BEGIN_syrk]
  //
  // Compute:
  // \begin{equation*}
  // M_0 = \alpha M_1\text{transpose}(M_2) + \beta M_3
  // \end{equation*}
  // where:
  // - $M_1, M_2$ : dense matrices
  // - $M_0, M_3$ : dense symmetric matrices
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
      // [END_syrk]
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

    assert(are_not_aliased_p(matrix0.impl(), matrix1.impl()));

    Blas::syrk_AAt(alpha.value(), matrix1, beta.value(), matrix0);

    DEBUG_SET_SELECTED(selected);
  }

  // template <typename ALPHA_IMPL,
  //           typename BETA_IMPL,
  //           typename MATRIX0_IMPL,
  //           typename MATRIX1_IMPL,
  //           typename MATRIX2_IMPL>
  // auto
  // assign(const Expr_Selector<Expr_Selector_Enum::Blas>& selected,
  //        Dense_Matrix_Crtp<MATRIX0_IMPL>& matrix0,
  //        const _plus_t_,
  //        const _product_t_,
  //        const _product_t_,
  //        const Scalar_Crtp<ALPHA_IMPL>& alpha,
  //        const _identity_t_,
  //        const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
  //        const _transpose_t_,
  //        const Dense_Matrix_Crtp<MATRIX2_IMPL>& matrix2,
  //        const _product_t_,
  //        const Scalar_Crtp<BETA_IMPL>& beta,
  //        const Matrix_LHS<MATRIX0_IMPL>& matrix3)

  //     -> std::enable_if_t<
  //         Is_Symmetric_Matrix_v<MATRIX0_IMPL> and Is_Full_Matrix_v<MATRIX1_IMPL> and
  //         Is_Full_Matrix_v<MATRIX2_IMPL> and
  //         Always_True_v<decltype(Blas::syrk_AAt(alpha.value(), matrix1, beta.value(), matrix0))>>

  // {
  //   assert(same_mathematical_object_p(matrix0.impl(), matrix3.impl()));
  //   assert(same_mathematical_object_p(matrix1.impl(), matrix2.impl()));

  //   Blas::syrk_AAt(alpha.value(), matrix1, beta.value(), matrix0);

  //   DEBUG_SET_SELECTED(selected);
  // }

  // [BEGIN_syrk]
  //
  // Compute:
  // \begin{equation*}
  // M_0 = \alpha \text{transpose}(M_1)M_2 + \beta M_3
  // \end{equation*}
  // where:
  // - $M_1, M_2$ : dense matrices
  // - $M_0, M_3$ : dense symmetric matrices
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
      // [END_syrk]
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

    assert(are_not_aliased_p(matrix0.impl(), matrix1.impl()));

    Blas::syrk_AtA(alpha.value(), matrix1, beta.value(), matrix0);

    DEBUG_SET_SELECTED(selected);
  }

  // [BEGIN_gemm]
  //
  // Compute:
  // \begin{equation*}
  //   M_0 = \alpha \text{op}_1(M_1) \text{op}_2(M_2) + \beta M_3
  // \end{equation*}
  // where:
  // - $M_0, M_1, M_2, M_3$ : dense matrices
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
      // [END_gemm]
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

    assert(are_not_aliased_p(matrix0.impl(), matrix1.impl()) and
           are_not_aliased_p(matrix0.impl(), matrix2.impl()));

    Blas::gemm(alpha.value(), op1, matrix1, op2, matrix2, beta.value(), matrix0);

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra

#endif
