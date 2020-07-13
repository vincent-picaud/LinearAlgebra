// [[file:v_eq_aMv_bv.org]]
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/expr/v_eq_aMv_bv/blas.hpp"

namespace LinearAlgebra
{
  // [BEGIN_assign]
  //
  // \begin{equation*}
  // v_0 = \alpha \text{op}_1(M_1) v_1 + \beta v_0
  // \end{equation*}
  //
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  // [END_assign]
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(v0.impl()) ==
           matrix_op(op1, dimension_predicate(M1)) * dimension_predicate(v1) +
               dimension_predicate(v0));

    // Delegate computation
    //
    assign(Expr_Selector<>(),
           v0.impl(),
           _plus_,
           _product_,
           _product_,
           alpha.impl(),
           op1,
           M1.impl(),
           v1.impl(),
           _product_,
           beta.impl(),
           v2.impl());
  }

  // ////////////////////////////////////////////////////////////////
  // Alias
  // ////////////////////////////////////////////////////////////////

  // [BEGIN_alias]
  // \begin{equation*} v_0 = M_1 v_1 + \beta v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(
        v0, _plus_, _product_, _product_, Scalar<int>{1}, _identity_, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = M_1 v_1 - v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL, typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }
  // [BEGIN_alias]
  // \begin{equation*} v_0 = M_1 v_1 + v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL, typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 + M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename V2_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 + \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 + \alpha M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(
        v0, _plus_, _product_, _product_, alpha, _identity_, M1, v1, _product_, Scalar<int>{1}, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 + \alpha \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _plus_, _product_, _product_, alpha, op1, M1, v1, _product_, Scalar<int>{1}, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 - M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename V2_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 - \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = v_2 - \alpha M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           ALPHA_IMPL{-alpha.value()},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \text{op}_1(M_1) v_1 + v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \text{op}_1(M_1) v_1 + \beta v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0, _plus_, _product_, _product_, Scalar<int>{1}, op1, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \text{op}_1(M_1) v_1 - v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \alpha M_1 v_1 + \beta v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0, _plus_, _product_, _product_, alpha, _identity_, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \alpha M_1 v_1 - \beta v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           alpha,
           _identity_,
           M1,
           v1,
           _product_,
           BETA_IMPL{-beta.value()},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \alpha M_1 v_1 + v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(
        v0, _plus_, _product_, _product_, alpha, _identity_, M1, v1, _product_, Scalar<int>{1}, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \alpha M_1 v_1 - v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           alpha,
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \alpha \text{op}_1(M_1) v_1 + v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0, _plus_, _product_, _product_, alpha, op1, M1, v1, _product_, Scalar<int>{1}, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \alpha \text{op}_1(M_1) v_1 - v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0, _plus_, _product_, _product_, alpha, op1, M1, v1, _product_, Scalar<int>{-1}, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 + \alpha M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _plus_, _product_, _product_, alpha, _identity_, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 - \alpha M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           ALPHA_IMPL{-alpha.value()},
           _identity_,
           M1,
           v1,
           _product_,
           beta,
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 + M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(
        v0, _plus_, _product_, _product_, Scalar<int>{1}, _identity_, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 + \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _plus_, _product_, _product_, Scalar<int>{1}, op1, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 + \alpha \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _plus_, _product_, _product_, alpha, op1, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 - M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(
        v0, _plus_, _product_, _product_, Scalar<int>{-1}, _identity_, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 - \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _plus_, _product_, _product_, Scalar<int>{-1}, op1, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = \beta v_2 - \alpha \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           ALPHA_IMPL{-alpha.value()},
           op1,
           M1,
           v1,
           _product_,
           beta,
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -M_1 v_1 + v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL, typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _unary_minus_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -M_1 v_1 + \beta v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _unary_minus_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(
        v0, _plus_, _product_, _product_, Scalar<int>{-1}, _identity_, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -M_1 v_1 - v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL, typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const _unary_minus_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -v_2 + M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename V2_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _unary_minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -v_2 + \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _unary_minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -v_2 + \alpha M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _unary_minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           alpha,
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -v_2 + \alpha \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            typename ALPHA_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _unary_minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0, _plus_, _product_, _product_, alpha, op1, M1, v1, _product_, Scalar<int>{-1}, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -v_2 - M_1 v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL, typename V2_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _unary_minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           _identity_,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -v_2 - \text{op}_1(M_1) v_1 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            typename V2_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _unary_minus_t_,
         const Vector_Crtp<V2_IMPL>& v2,
         const _product_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -\text{op}_1(M_1) v_1 + v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _unary_minus_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{1},
           v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -\text{op}_1(M_1) v_1 + \beta v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename BETA_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const _unary_minus_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const _product_t_,
         const Scalar_Crtp<BETA_IMPL>& beta,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0, _plus_, _product_, _product_, Scalar<int>{-1}, op1, M1, v1, _product_, beta, v2);
  }

  // [BEGIN_alias]
  // \begin{equation*} v_0 = -\text{op}_1(M_1) v_1 - v_2 \end{equation*}
  // [END_alias]
  template <typename V0_IMPL,
            Matrix_Unary_Op_Enum OP1,
            typename M1_IMPL,
            typename V1_IMPL,
            typename V2_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _minus_t_,
         const _product_t_,
         const _unary_minus_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
  {
    assign(v0,
           _plus_,
           _product_,
           _product_,
           Scalar<int>{-1},
           op1,
           M1,
           v1,
           _product_,
           Scalar<int>{-1},
           v2);
  }

  // [END_alias]
  //
}  // namespace LinearAlgebra
