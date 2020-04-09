//
// The role of this file is to reduce expression to this form
//
//   V0 = α op(M) V1 + β V2
//
// This file does not contain computational routine
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_is_same.hpp"

#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

#include <csignal>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  //
  // V0 = alpha * transpose(M1) * V1 + beta * V2
  // vector0 = + * * alpha op1 matrix1 vector1 * beta vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    static_assert(Always_False_v<MATRIX1_IMPL>, "Not implemented");

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op1, dimension_predicate(matrix1)) * dimension_predicate(vector1) +
           dimension_predicate(vector0));

    //    std::raise(SIGINT);

    // Delegate computation
    //
    if (not is_same(vector0.impl(), vector2.impl()))
    {
      // vector0 = vector2;
      assign(vector0, vector2);
    }
    assign(Expr_Selector<>(), vector0.impl(), _plus_, _product_, _product_, alpha, op1,
                  matrix1.impl(), vector1.impl(), _product_, beta, _lhs_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //   PRINT_EXPR(V0, M1 * V1 + V2);
  //   PRINT_EXPR(V0, M1 * V1 + beta * V2);
  //   PRINT_EXPR(V0, M1 * V1 - V2);
  //   PRINT_EXPR(V0, V2 + M1 * V1);
  //   PRINT_EXPR(V0, V2 + transpose(M1) * V1);
  //   PRINT_EXPR(V0, V2 + alpha * M1 * V1);
  //   PRINT_EXPR(V0, V2 + alpha * transpose(M1) * V1);
  //   PRINT_EXPR(V0, V2 - M1 * V1);
  //   PRINT_EXPR(V0, V2 - transpose(M1) * V1);
  //   PRINT_EXPR(V0, V2 - alpha * M1 * V1);
  //   PRINT_EXPR(V0, transpose(M1) * V1 + V2);
  //   PRINT_EXPR(V0, transpose(M1) * V1 + beta * V2);
  //   PRINT_EXPR(V0, transpose(M1) * V1 - V2);
  //   PRINT_EXPR(V0, alpha * M1 * V1 + beta * V2);
  //   PRINT_EXPR(V0, alpha * M1 * V1 - beta * V2);
  //   PRINT_EXPR(V0, alpha * M1 * V1 + V2);
  //   PRINT_EXPR(V0, alpha * M1 * V1 - V2);
  //   PRINT_EXPR(V0, alpha * transpose(M1) * V1 + V2);
  //   PRINT_EXPR(V0, alpha * transpose(M1) * V1 - V2);
  //   PRINT_EXPR(V0, alpha * transpose(M1) * V1 + beta * V2);
  //   PRINT_EXPR(V0, beta * V2 + alpha * M1 * V1);
  //   PRINT_EXPR(V0, beta * V2 - alpha * M1 * V1);
  //   PRINT_EXPR(V0, beta * V2 + M1 * V1);
  //   PRINT_EXPR(V0, beta * V2 + transpose(M1) * V1);
  //   PRINT_EXPR(V0, beta * V2 + alpha * transpose(M1) * V1);
  //   PRINT_EXPR(V0, beta * V2 - M1 * V1);
  //   PRINT_EXPR(V0, beta * V2 - transpose(M1) * V1);
  //   PRINT_EXPR(V0, beta * V2 - alpha * transpose(M1) * V1);
  //   PRINT_EXPR(V0, -M1 * V1 + V2);
  //   PRINT_EXPR(V0, -M1 * V1 + beta * V2);
  //   PRINT_EXPR(V0, -M1 * V1 - V2);
  //   PRINT_EXPR(V0, -V2 + M1 * V1);
  //   PRINT_EXPR(V0, -V2 + transpose(M1) * V1);
  //   PRINT_EXPR(V0, -V2 + alpha * M1 * V1);
  //   PRINT_EXPR(V0, -V2 + alpha * transpose(M1) * V1);
  //   PRINT_EXPR(V0, -V2 - M1 * V1);
  //   PRINT_EXPR(V0, -V2 - transpose(M1) * V1);
  //   PRINT_EXPR(V0, -transpose(M1) * V1 + V2);
  //   PRINT_EXPR(V0, -transpose(M1) * V1 + beta * V2);
  //   PRINT_EXPR(V0, -transpose(M1) * V1 - V2);

  //
  // V0 = M1 * V1 + V2
  // vector0 = + * matrix1 vector1 vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = M1 * V1 + beta * V2
  // vector0 = + * matrix1 vector1 * beta vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = M1 * V1 - V2
  // vector0 = - * matrix1 vector1 vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = V2 + M1 * V1
  // vector0 = + vector2 * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = V2 + transpose(M1) * V1
  // vector0 = + vector2 * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, op1, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = V2 + alpha * M1 * V1
  // vector0 = + vector2 * * alpha matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = V2 + alpha * transpose(M1) * V1
  // vector0 = + vector2 * * alpha op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, op1, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = V2 - M1 * V1
  // vector0 = - vector2 * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = V2 - transpose(M1) * V1
  // vector0 = - vector2 * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, op1, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = V2 - alpha * M1 * V1
  // vector0 = - vector2 * * alpha matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = transpose(M1) * V1 + V2
  // vector0 = + * op1 matrix1 vector1 vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, op1, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = transpose(M1) * V1 + beta * V2
  // vector0 = + * op1 matrix1 vector1 * beta vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, op1, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = transpose(M1) * V1 - V2
  // vector0 = - * op1 matrix1 vector1 vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, op1, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = alpha * M1 * V1 + beta * V2
  // vector0 = + * * alpha matrix1 vector1 * beta vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = alpha * M1 * V1 - beta * V2
  // vector0 = - * * alpha matrix1 vector1 * beta vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -beta, vector2.impl());
  }

  //
  // V0 = alpha * M1 * V1 + V2
  // vector0 = + * * alpha matrix1 vector1 vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = alpha * M1 * V1 - V2
  // vector0 = - * * alpha matrix1 vector1 vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = alpha * transpose(M1) * V1 + V2
  // vector0 = + * * alpha op1 matrix1 vector1 vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, op1, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = alpha * transpose(M1) * V1 - V2
  // vector0 = - * * alpha op1 matrix1 vector1 vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, op1, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = beta * V2 + alpha * M1 * V1
  // vector0 = + * beta vector2 * * alpha matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 - alpha * M1 * V1
  // vector0 = - * beta vector2 * * alpha matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 + M1 * V1
  // vector0 = + * beta vector2 * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 + transpose(M1) * V1
  // vector0 = + * beta vector2 * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, op1, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 + alpha * transpose(M1) * V1
  // vector0 = + * beta vector2 * * alpha op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, op1, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 - M1 * V1
  // vector0 = - * beta vector2 * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 - transpose(M1) * V1
  // vector0 = - * beta vector2 * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, op1, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = beta * V2 - alpha * transpose(M1) * V1
  // vector0 = - * beta vector2 * * alpha op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -alpha, op1, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = -M1 * V1 + V2
  // vector0 = + * - matrix1 vector1 vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _unary_minus_t_, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = -M1 * V1 + beta * V2
  // vector0 = + * - matrix1 vector1 * beta vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _unary_minus_t_, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = -M1 * V1 - V2
  // vector0 = - * - matrix1 vector1 vector2
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const _unary_minus_t_, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1, const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -V2 + M1 * V1
  // vector0 = + - vector2 * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _unary_minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -V2 + transpose(M1) * V1
  // vector0 = + - vector2 * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _unary_minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, 1, op1, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -V2 + alpha * M1 * V1
  // vector0 = + - vector2 * * alpha matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _unary_minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -V2 + alpha * transpose(M1) * V1
  // vector0 = + - vector2 * * alpha op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _unary_minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_, const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, alpha, op1, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -V2 - M1 * V1
  // vector0 = - - vector2 * matrix1 vector1
  //
  template <typename VECTOR0_IMPL, typename VECTOR1_IMPL, typename VECTOR2_IMPL,
            typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _unary_minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, _identity_, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -V2 - transpose(M1) * V1
  // vector0 = - - vector2 * op1 matrix1 vector1
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _unary_minus_t_,
         const Vector_Crtp<VECTOR2_IMPL>& vector2, const _product_t_,
         const _matrix_unary_op_t_<OP1_ENUM> op1, const Matrix_Crtp<MATRIX1_IMPL>& matrix1,
         const Vector_Crtp<VECTOR1_IMPL>& vector1)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, op1, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

  //
  // V0 = -transpose(M1) * V1 + V2
  // vector0 = + * - op1 matrix1 vector1 vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _unary_minus_t_, const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, op1, matrix1.impl(),
                  vector1.impl(), _product_, +1, vector2.impl());
  }

  //
  // V0 = -transpose(M1) * V1 + beta * V2
  // vector0 = + * - op1 matrix1 vector1 * beta vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _plus_t_, const _product_t_,
         const _unary_minus_t_, const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const _product_t_,
         const Common_Element_Type_t<VECTOR0_IMPL, VECTOR1_IMPL, VECTOR2_IMPL, MATRIX1_IMPL>& beta,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, op1, matrix1.impl(),
                  vector1.impl(), _product_, beta, vector2.impl());
  }

  //
  // V0 = -transpose(M1) * V1 - V2
  // vector0 = - * - op1 matrix1 vector1 vector2
  //
  template <Matrix_Unary_Op_Enum OP1_ENUM, typename VECTOR0_IMPL, typename VECTOR1_IMPL,
            typename VECTOR2_IMPL, typename MATRIX1_IMPL>
  void
  assign(Vector_Crtp<VECTOR0_IMPL>& vector0, const _minus_t_, const _product_t_,
         const _unary_minus_t_, const _matrix_unary_op_t_<OP1_ENUM> op1,
         const Matrix_Crtp<MATRIX1_IMPL>& matrix1, const Vector_Crtp<VECTOR1_IMPL>& vector1,
         const Vector_Crtp<VECTOR2_IMPL>& vector2)
  {
    assign(vector0.impl(), _plus_, _product_, _product_, -1, op1, matrix1.impl(),
                  vector1.impl(), _product_, -1, vector2.impl());
  }

}
