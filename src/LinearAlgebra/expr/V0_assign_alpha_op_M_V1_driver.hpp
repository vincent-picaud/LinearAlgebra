//
// V0 = α op(M) V1
//
// V0 = α op(inverse(M)) V1
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
  // vector0 = alpha * transpose(M1) * vector1
  // vector0 = * * alpha op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    static_assert(Always_False_v<MATRIX1_IMPL>, "Not implemented");
    return selected;
  }

  //
  // vector0 = alpha * transpose(inverse(M1)) * vector1
  // vector0 = * * alpha op1 inverse matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const _inverse_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    static_assert(Always_False_v<MATRIX1_IMPL>, "Not implemented");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(vector0) ==
           matrix_op(op1, dimension_predicate(matrix1)) * dimension_predicate(vector1));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), vector0.impl(), _product_, _product_, alpha, op1,
                  matrix1.impl(), vector1.impl());
  }
  // inverse
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  Expr_Selector_Enum
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const _inverse_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)

  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix1.I_size() == matrix1.J_size());  // inverse => square
    assert(dimension_predicate(vector0) ==
           matrix_op(op1, dimension_predicate(matrix1)) * dimension_predicate(vector1));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), vector0.impl(), _product_, _product_, alpha, op1, _inverse_,
                  matrix1.impl(), vector1.impl());
  }
  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  // PRINT_EXPR(V0, M1 * V1);
  // PRINT_EXPR(V0, inverse(M1) * V1);
  // PRINT_EXPR(V0, alpha * M1 * V1);
  // PRINT_EXPR(V0, alpha * inverse(M1) * V1);
  // PRINT_EXPR(V0, transpose(M1) * V1);
  // PRINT_EXPR(V0, inverse(transpose(M1)) * V1);
  // PRINT_EXPR(V0, transpose(inverse(M1)* V1));
  // PRINT_EXPR(V0, alpha * inverse(transpose(M1))* V1);

  //
  // V0 = M1 * V1
  // vector0 = * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = inverse(M1) * V1
  // vector0 = * inverse matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _inverse_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = alpha * M1 * V1
  // vector0 = * * alpha matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = alpha * inverse(M1) * V1
  // vector0 = * * alpha inverse matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _inverse_t_, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = transpose(M1) * V1
  // vector0 = * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = inverse(transpose(M1)) * V1
  // vector0 = * inverse op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _inverse_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = transpose(inverse(M1)* V1)
  // vector0 = op1 * inverse matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _matrix_unary_op_t_<OP1_ENUM> op1,
         const _product_t_, const _inverse_t_, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

  //
  // V0 = alpha * inverse(transpose(M1))* V1
  // vector0 = * * alpha inverse op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, MATRIX1_IMPL>& alpha,
         const _inverse_t_, const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assert(0);
  }

}
