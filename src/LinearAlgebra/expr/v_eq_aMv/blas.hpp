// [[file:blas.org]]
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#ifdef HAS_BLAS

#include "LinearAlgebra/dense/memory_chunk_aliasing_p.hpp"
#include "LinearAlgebra/expr/X_eq_aX_vector.hpp"
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  //  gemv
  // ////////////////////////////////////////////////////////////////
  //
  // [BEGIN_gemv]
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
          Always_True_v<decltype(Blas::gemv(alpha.value(), op1, matrix1, vector1, 0, vector0))>>
  {
    assert(are_not_aliased_p(vector0, matrix1));
    assert(are_not_aliased_p(vector0, vector1));

    Blas::gemv(alpha.value(), op1, matrix1, vector1, 0, vector0);

    DEBUG_SET_SELECTED(selected);
  }
  // [END_gemv]

  // ////////////////////////////////////////////////////////////////
  //  symv
  // ////////////////////////////////////////////////////////////////
  //
  // [BEGIN_symv]
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
          Always_True_v<decltype(Blas::symv(alpha.value(), op1, matrix1, vector1, 0, vector0))>>
  {
    assert(are_not_aliased_p(vector0, matrix1));
    assert(are_not_aliased_p(vector0, vector1));

    Blas::symv(alpha.value(), op1, matrix1, vector1, 0, vector0);

    DEBUG_SET_SELECTED(selected);
  }

  // [END_symv]

  // ////////////////////////////////////////////////////////////////
  //  trmv
  // ////////////////////////////////////////////////////////////////
  //
  // [BEGIN_trmv]
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
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(vector1, vector0))> and
                          Always_True_v<decltype(Blas::scal(alpha.value(), vector0))> and
                          Always_True_v<decltype(Blas::trmv(op1, matrix1, vector0))>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case

    if (not same_mathematical_object_p(vector0, vector1))
    {
      Blas::copy(vector1, vector0);
    }

    assert(are_not_aliased_p(vector0, matrix1));
    assert(same_mathematical_object_p(vector0, vector1));

    Blas::scal(alpha.value(), vector0);
    Blas::trmv(op1, matrix1, vector0);

    DEBUG_SET_SELECTED(selected);
  }
  // [END_trmv]

}  // namespace LinearAlgebra

#endif
