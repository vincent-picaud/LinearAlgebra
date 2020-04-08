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
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& beta, const _lhs_t_)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>, Element_Type_t<VECTOR0_IMPL>,
                              Element_Type_t<VECTOR1_IMPL>> &&
              // Scalar support
              Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
              // Generic matrix
              (MATRIX1_IMPL::matrix_special_structure_type::value ==
               Matrix_Special_Structure_Enum::None),
          Expr_Selector_Enum>
  {
    assert(are_not_aliased_p(vector0, vector1) and are_not_aliased_p(vector0, matrix1));

    Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<OP1_ENUM>, matrix1.I_size(),
               matrix1.J_size(), alpha, matrix1.data(), matrix1.leading_dimension(), vector1.data(),
               vector1.increment(), beta, vector0.data(), vector0.increment());
    return selected;
  }

  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Dense_Vector_Crtp<VECTOR2_IMPL>& vector2)
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP1_ENUM> &&
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>, Element_Type_t<VECTOR0_IMPL>,
                              Element_Type_t<VECTOR1_IMPL>, Element_Type_t<VECTOR2_IMPL>> &&
              // Scalar support
              Blas::Is_CBlas_Supported_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
              // Generic matrix
              (MATRIX1_IMPL::matrix_special_structure_type::value ==
               Matrix_Special_Structure_Enum::None),
          Expr_Selector_Enum>
  {
    vector0 = vector2;
    return assign(selected, vector0, alpha, op1, matrix1, vector1, _plus_, beta, _lhs_);
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
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Dense_Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& beta, const _lhs_t_)
      -> std::enable_if_t<
          // Supported matrix op?
          (OP1_ENUM == Matrix_Unary_Op_Enum::Identity or
           OP1_ENUM == Matrix_Unary_Op_Enum::Transpose) and
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<MATRIX1_IMPL>, Element_Type_t<VECTOR0_IMPL>,
                              Element_Type_t<VECTOR1_IMPL>> &&
              // Scalar support
              Blas::Is_CBlas_Supported_Real_Scalar_v<Element_Type_t<MATRIX1_IMPL>> &&
              // Matrix structure
              (MATRIX1_IMPL::matrix_special_structure_type::value ==
               Matrix_Special_Structure_Enum::Symmetric),
          Expr_Selector_Enum>
  {
    // Sanity check
    assert(matrix1.I_size() == matrix1.J_size());
    assert(are_not_aliased_p(vector0, vector1) and are_not_aliased_p(vector0, matrix1));

    Blas::symv(CblasColMajor, Blas::To_CBlas_UpLo_v<MATRIX1_IMPL::matrix_storage_mask_type::value>,
               matrix1.I_size(), alpha, matrix1.data(), matrix1.leading_dimension(), vector1.data(),
               vector1.increment(), beta, vector0.data(), vector0.increment());
    return selected;
  }

}

#endif
