#pragma once

#include "LinearAlgebra/expr/M_eq_aMM_bM/M0_eq_aM1M1_bM0.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/all_same_type.hpp"

namespace LinearAlgebra
{
#if (HAS_BLAS)
  //
  // M0 := α.M1.M1^t + β.M0
  // or
  // M0 := α.M1^t.M1 + β.M0
  //
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM,
            Matrix_Unary_Op_Enum OP2_ENUM,
            typename MATRIX0_IMPL,
            typename MATRIX1_IMPL>
  std::enable_if_t<
      // Supported matrix op?
      ((OP1_ENUM == Matrix_Unary_Op_Enum::Identity &&
        (OP2_ENUM == Matrix_Unary_Op_Enum::Transpose ||
         OP2_ENUM == Matrix_Unary_Op_Enum::TransConj)) ||
       ((OP1_ENUM == Matrix_Unary_Op_Enum::Transpose ||
         OP1_ENUM == Matrix_Unary_Op_Enum::TransConj) &&
        OP2_ENUM == Matrix_Unary_Op_Enum::Identity)) &&

      // Same scalar everywhere
      All_Same_Type_v<Element_Type_t<MATRIX0_IMPL>, Element_Type_t<MATRIX1_IMPL>> &&

      // Scalar support
      Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX0_IMPL>> &&

      // Matrix type
      (MATRIX0_IMPL::matrix_special_structure_type::value ==
       Matrix_Special_Structure_Enum::Symmetric) &&
      (MATRIX1_IMPL::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None)>
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Matrix_Crtp<MATRIX0_IMPL>& matrix0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Common_Element_Type_t<MATRIX0_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _matrix_unary_op_t_<OP2_ENUM> op2,
         const _rhs_1_t_,
         const _product_t_,
         const Common_Element_Type_t<MATRIX0_IMPL, MATRIX1_IMPL>& beta,
         const _lhs_t_)

  {
    assert(are_not_aliased_p(matrix0.impl(), matrix1.impl()));

    DEBUG_SET_SELECTED(selected);

    // (what=1) C := alpha*A*A' + beta*C
    // (what=2) C := alpha*A'*A + beta*C
    constexpr int what = (OP1_ENUM == Matrix_Unary_Op_Enum::Identity &&
                          (OP2_ENUM == Matrix_Unary_Op_Enum::Transpose ||
                           OP2_ENUM == Matrix_Unary_Op_Enum::TransConj))
                             ? 1
                             : 2;

    std::size_t K;
    CBLAS_TRANSPOSE Trans;

    if constexpr (what == 1)
    {
      K     = matrix1.J_size();
      Trans = Blas::To_CBlas_Transpose_v<Matrix_Unary_Op_Enum::Identity>;
    }
    else
    {
      K     = matrix1.I_size();
      Trans = Blas::To_CBlas_Transpose_v<Matrix_Unary_Op_Enum::Transpose>;
    }

    Blas::syrk(CblasColMajor,
               Blas::To_CBlas_UpLo_v<MATRIX0_IMPL::matrix_storage_mask_type::value>,
               Trans,
               matrix0.I_size(),
               K,
               alpha,
               matrix1.data(),
               matrix1.leading_dimension(),
               beta,
               matrix0.data(),
               matrix0.leading_dimension());
  }

#endif
}
