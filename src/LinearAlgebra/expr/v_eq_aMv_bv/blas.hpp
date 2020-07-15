// [[file:blas.org]]
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#ifdef HAS_BLAS

#include "LinearAlgebra/expr/copy.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

namespace LinearAlgebra
{
  // [BEGIN_gemv]
  //
  // \begin{equation*}
  //   v_0=\alpha \text{op}(M_1)v_1 +\beta v_2
  // \end{equation*}
  //
  // where:
  // - $M_1$ : dense matrix
  //
  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL,
            typename VECTOR2_IMPL>
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
      // [END_gemv]
      -> std::enable_if_t<Always_True_v<
          decltype(Blas::gemv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0))>>
  {
    if (not same_mathematical_object_p(vector0.impl(), vector2.impl()))
    {
      assign(vector0, vector2);
    }

    assert(are_not_aliased_p(vector0, vector1) and are_not_aliased_p(vector0, matrix1));

    Blas::gemv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0);

    DEBUG_SET_SELECTED(selected);
  }

  // [BEGIN_symv]
  //
  // \begin{equation*}
  //   v_0=\alpha \text{op}(M_1)v_1 +\beta v_2
  // \end{equation*}
  //
  // where:
  // - $M_1$ : dense *symmetric* matrix
  //
  template <typename ALPHA_IMPL,
            typename BETA_IMPL,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename VECTOR0_IMPL,
            typename VECTOR1_IMPL,
            typename MATRIX1_IMPL,
            typename VECTOR2_IMPL>
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
      // [END_symv]
      -> std::enable_if_t<Always_True_v<
          decltype(Blas::symv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0))>>
  {
    if (not same_mathematical_object_p(vector0.impl(), vector2.impl()))
    {
      assign(vector0, vector2);
    }

    assert(are_not_aliased_p(vector0, vector1) and are_not_aliased_p(vector0, matrix1));

    Blas::symv(alpha.value(), op1, matrix1, vector1, beta.value(), vector0);

    DEBUG_SET_SELECTED(selected);
  }
}  // namespace LinearAlgebra

#elif
#error debug
#endif
