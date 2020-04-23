#pragma once

#include "LinearAlgebra/expr/M_eq_aMM_bM/M0_eq_aMM_bM0.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/all_same_type.hpp"

namespace LinearAlgebra
{
#if (HAS_BLAS)
  template <typename M0_TYPE,
            Matrix_Unary_Op_Enum OP1_ENUM,
            typename M1_TYPE,
            Matrix_Unary_Op_Enum OP2_ENUM,
            typename M2_TYPE>
  std::enable_if_t<
      // Supported matrix op?
      ((OP1_ENUM == Matrix_Unary_Op_Enum::Identity &&
        (OP2_ENUM == Matrix_Unary_Op_Enum::Transpose ||
         OP2_ENUM == Matrix_Unary_Op_Enum::TransConj)) ||
       ((OP1_ENUM == Matrix_Unary_Op_Enum::Transpose ||
         OP1_ENUM == Matrix_Unary_Op_Enum::TransConj) &&
        OP2_ENUM == Matrix_Unary_Op_Enum::Identity)) &&

      // Same scalar everywhere
      All_Same_Type_v<Element_Type_t<M0_TYPE>, Element_Type_t<M1_TYPE>, Element_Type_t<M2_TYPE>> &&

      // Scalar support
      Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<M0_TYPE>> &&

      // Matrix type
      (M0_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::Symmetric) &&
      (M1_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None) &&
      (M2_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None)>
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,        //
         Matrix_Crtp<M0_TYPE>& M0,                                      //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE, M2_TYPE> alpha,  //
         const _matrix_unary_op_t_<OP1_ENUM> op1,                       //
         const Matrix_Crtp<M1_TYPE>& M1,                                //
         const _matrix_unary_op_t_<OP2_ENUM> op2,                       //
         const Matrix_Crtp<M2_TYPE>& M2,                                //
         const _plus_t_,                                                //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE, M2_TYPE> beta,   //
         const _lhs_t_)                                                 //

  {
    assert(are_not_aliased_p(M0.impl(), M1.impl()));
    assert(are_not_aliased_p(M0.impl(), M2.impl()));

    DEBUG_SET_SELECTED(selected);

    // (what=1) C := alpha*A*A' + beta*C
    // (what=2) C := alpha*A'*A + beta*C
    constexpr int what = (OP1_ENUM == Matrix_Unary_Op_Enum::Identity &&
                          (OP2_ENUM == Matrix_Unary_Op_Enum::Transpose ||
                           OP2_ENUM == Matrix_Unary_Op_Enum::TransConj))
                             ? 1
                             : 2;

    // std::size_t K;
    // CBLAS_TRANSPOSE Trans;

    // if constexpr (what==1) {
    // 	K=

    //   }
    //  syrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE Trans,
    //    const std::size_t N, const std::size_t K, const std::complex<double> &alpha,
    //    const std::complex<double> *A, const std::size_t lda, const std::complex<double> &beta,
    //    std::complex<double> *C, const std::size_t ldc)
    assert(0);
  }

#endif
}
