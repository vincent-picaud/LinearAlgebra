//
// V0 = α op(M) V0
//
// V0 = α op(inverse(M)) V0
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * transpose(M1) * V0
  // vector0 = * * alpha op1 matrix1 vector0
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _lhs_t_)
  {
    static_assert(Always_False_v<MATRIX1_IMPL>, "Not implemented");
    return selected;
  }

  //
  // V0 = alpha * transpose(inverse(M1)) * V0
  // vector0 = * * alpha op1 inverse matrix1 vector0
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const _inverse_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const _lhs_t_)
  {
    static_assert(not std::is_same_v<MATRIX1_IMPL, MATRIX1_IMPL>, "Not implemented");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const _lhs_t_)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(vector0) ==
           matrix_op(op1, dimension_predicate(matrix1)) * dimension_predicate(vector0));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), vector0.impl(), _product_, _product_, alpha, op1,
                  matrix1.impl(), _lhs_);
  }
  // inverse
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const _inverse_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const _lhs_t_)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(vector0) ==
           matrix_op(op1, dimension_predicate(matrix1)) * dimension_predicate(vector0));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), vector0.impl(), _product_, _product_, alpha, op1, _inverse_,
                  matrix1.impl(), _lhs_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //
  // CAVEAT: as it use _lhs_t_, thus cannot be called from metaExpr, it
  //         is useless to define any alias
  //
}
