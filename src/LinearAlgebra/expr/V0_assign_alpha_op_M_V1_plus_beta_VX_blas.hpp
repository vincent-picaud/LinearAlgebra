//
// blas gemv routine for
//
//   V0 = α op(M) V1 + β V2
//
#pragma once
#include <csignal>
#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"

#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V0_driver.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V2_driver.hpp"

#include "LinearAlgebra/utils/all_same_type.hpp"

#include "LinearAlgebra/blas/blas.hpp"

#if (HAS_BLAS)

namespace LinearAlgebra
{
  //================================================================
  // GEMV V0 = α op(M) V1 + β V0
  //================================================================
  //
  //
  //
  // V0 = alpha * transpose(M1) * V1 + beta * V0
  // vector0 = + * * alpha op1 matrix1 vector1 * beta vector0
  //
  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const _lhs_t_)
      -> std::enable_if_t<Always_True_v<
          decltype(Blas::gemv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0))>>
  {
    assert(are_not_aliased_p(vector0, vector1) and are_not_aliased_p(vector0, matrix1));
    Blas::gemv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0);

    DEBUG_SET_SELECTED(selected);
  }

  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Dense_Vector_Crtp<VECTOR2_IMPL>& vector2)
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(vector2, vector0))> and
                          Always_True_v<decltype(Blas::gemv(
                              alpha.value(), op1, matrix1, vector1, beta.value(), vector0))>>
  {
    Blas::copy(vector2, vector0);
    Blas::gemv(alpha, op1, matrix1, vector1, beta, vector0);
  }

  //================================================================
  // SYMV V0 = α op(M) V1 + β V0
  //================================================================
  //
  // op is restricted to identity & transpose
  // element_type must be real
  //
  //
  // V0 = alpha * transpose(M1) * V1 + beta * V0
  // vector0 = + * * alpha op1 matrix1 vector1 * beta vector0
  //
  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const _lhs_t_)
      -> std::enable_if_t<Always_True_v<
          decltype(Blas::symv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0))>>
  {
    // Sanity check
    assert(matrix1.I_size() == matrix1.J_size());
    assert(are_not_aliased_p(vector0, vector1) and are_not_aliased_p(vector0, matrix1));

    Blas::symv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0);

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra

#endif
