// [[file:v_eq_aMv.org]]
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/expr/v_eq_aMv/blas.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  // v_0 = \alpha \text{op}_1(M_1) v_1
  // ////////////////////////////////////////////////////////////////

  // [BEGIN_assign]
  // \begin{equation*}
  // v_0 = \alpha \text{op}_1(M_1) v_1
  // \end{equation*}
  //
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  // [END_assign]
  {
    assert(dimension_predicate(v0.impl()) ==
           matrix_op(op1, dimension_predicate(M1)) * dimension_predicate(v1));

    assign(Expr_Selector<>(),
           v0.impl(),
           _product_t_,
           _product_t_,
           alpha.impl(),
           op1,
           M1.impl(),
           v1.impl());
  }

  // ////////////////////////////////////////////////////////////////
  // Alias
  // ////////////////////////////////////////////////////////////////
  //
  // PRINT_EXPR(v0, alpha * op1(M1) * v1);
  //
  // PRINT_EXPR(v0, -M1 * v1);
  // PRINT_EXPR(v0, -op1(M1) * v1);
  // PRINT_EXPR(v0, M1 * v1);
  // PRINT_EXPR(v0, alpha * M1 * v1);
  // PRINT_EXPR(v0, op1(M1) * v1);

  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = -M_1 v_1
  // \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _unary_minus_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _product_t_, _product_t_, Scalar<int>{-1}, _identity_, M1, v1);
  }
  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = -\text{op}_1(M_1) v_1
  // \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, Matrix_Unary_Op_Enum OP1, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _unary_minus_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _product_t_, _product_t_, Scalar<int>{-1}, op1, M1, v1);
  }
  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = M_1 v_1
  // \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _product_t_, _product_t_, Scalar<int>{1}, _identity_, M1, v1);
  }
  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = \alpha M_1 v_1
  // \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename ALPHA_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _product_t_, _product_t_, alpha, _identity_, M1, v1);
  }
  // [BEGIN_alias]
  // \begin{equation*}
  // v_0 = \text{op}_1(M_1) v_1
  // \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, Matrix_Unary_Op_Enum OP1, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _product_t_, _product_t_, Scalar<int>{1}, op1, M1, v1);
  }

  // v0 = alpha * op1(M1) * v1;
  // EXPECT_DOUBLE_EQ(*v0.data(),( ( 0.100000 ) * ( 0.002000 ) ) * ( 0.020000 ));

  // v0 = -M1 * v1;
  // EXPECT_DOUBLE_EQ(*v0.data(),( - ( 0.002000 ) ) * ( 0.020000 ));

  // v0 = -op1(M1) * v1;
  // EXPECT_DOUBLE_EQ(*v0.data(),( - ( 0.002000 ) ) * ( 0.020000 ));

  // v0 = M1 * v1;
  // EXPECT_DOUBLE_EQ(*v0.data(),( 0.002000 ) * ( 0.020000 ));

  // v0 = alpha * M1 * v1;
  // EXPECT_DOUBLE_EQ(*v0.data(),( ( 0.100000 ) * ( 0.002000 ) ) * ( 0.020000 ));

  // v0 = op1(M1) * v1;
  // EXPECT_DOUBLE_EQ(*v0.data(),( 0.002000 ) * ( 0.020000 ));

}  // namespace LinearAlgebra
