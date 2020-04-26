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
#include "LinearAlgebra/utils/same_mathematical_object_p.hpp"

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
  // vector0 = alpha * op(M1) * vector1
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
          Always_True_v<decltype(Blas::symv(alpha.value(), op1, matrix1, vector1, 0, vector0))>>
  {
    Blas::symv(alpha.value(), op1, matrix1, vector1, 0, vector0);

    // // redirect
    // assign(selected,
    //        vector0,
    //        _plus_,
    //        _product_,
    //        _product_,
    //        alpha.impl(),
    //        op1,
    //        matrix1,
    //        vector1,
    //        _product_,
    //        ALPHA_IMPL(0),
    //        _lhs_);

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////

  //================================================================
  // trmv
  //================================================================
  //
  //
  // VECTOR0 = alpha * op(M1) * VECTOR0
  // vector0 = * * alpha op1 matrix1 vector0
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
         const Dense_Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _lhs_t_)
      -> std::enable_if_t<Always_True_v<decltype(Blas::scal(alpha.value(), vector0))> and
                          Always_True_v<decltype(Blas::trmv(op1, matrix1, vector0))>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case
    assert(are_not_aliased_p(vector0, matrix1));

    Blas::scal(alpha.value(), vector0);
    Blas::trmv(op1, matrix1, vector0);

    DEBUG_SET_SELECTED(selected);
  }
  //
  // vector0 = alpha * op(M1) * vector1
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
          Always_True_v<decltype(Blas::copy(vector1, vector0))> and  // <-------------- here p
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
      -> std::enable_if_t<Always_True_v<decltype(Blas::scal(alpha.value(), vector0))> and
                          Always_True_v<decltype(Blas::trsv(op1, matrix1, vector0))>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case
    assert(are_not_aliased_p(vector0, matrix1));

    Blas::scal(alpha.value(), vector0);
    Blas::trsv(op1, matrix1, vector0);

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
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(vector1, vector0))> and
                          Always_True_v<decltype(Blas::scal(alpha.value(), vector0))> and
                          Always_True_v<decltype(Blas::trsv(op1, matrix1, vector0))>>
  {
    assert(matrix1.I_size() == matrix1.J_size());  // TODO: extend to the rectangular case

    if (not same_mathematical_object_p(vector0, vector1))
    {
      Blas::copy(vector1, vector0);
    }

    assert(are_not_aliased_p(vector0, matrix1));
    assert(same_mathematical_object_p(vector0, vector1));

    Blas::scal(alpha.value(), vector0);
    Blas::trsv(op1, matrix1, vector0);

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra

#endif
