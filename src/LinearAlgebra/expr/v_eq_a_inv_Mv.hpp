// [[file:v_eq_a_inv_Mv.org]]
#error TODO
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/expr/v_eq_a_inv_Mv/blas.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  // v_0 = \alpha \text{op}_1(M_1) v_1
  // ////////////////////////////////////////////////////////////////

  // [BEGIN_assign]
  // \begin{equation*}
  // v_0 = \alpha \text{inv}(\text{op}_1(M_1)) v_1
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
         const _inverse_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  // [END_assign]
  {
  }
  
  // ////////////////////////////////////////////////////////////////
  // Alias
  // ////////////////////////////////////////////////////////////////
  //
  // [DOC]
  //
  // \begin{equation*}
  // v_0 = -\text{inv}(M_1) v_1
  // \end{equation*}
  //
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _unary_minus_t_,
         const _inverse_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
  }
  // [DOC]
  //
  // \begin{equation*}
  // v_0 = -\text{inv}(\text{op}_1(M_1)) v_1
  // \end{equation*}
  //
  template <typename V0_IMPL, Matrix_Unary_Op_Enum OP1, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _unary_minus_t_,
         const _inverse_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
  }
  // [DOC]
  //
  // \begin{equation*}
  // v_0 = \text{inv}(M_1) v_1
  // \end{equation*}
  //
  template <typename V0_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _inverse_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
  }
  // [DOC]
  //
  // \begin{equation*}
  // v_0 = \alpha \text{inv}(M_1) v_1
  // \end{equation*}
  //
  template <typename V0_IMPL, typename ALPHA_IMPL, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _inverse_t_,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
  }
  // [DOC]
  //
  // \begin{equation*}
  // v_0 = \text{inv}(\text{op}_1(M_1)) v_1
  // \end{equation*}
  //
  template <typename V0_IMPL, Matrix_Unary_Op_Enum OP1, typename M1_IMPL, typename V1_IMPL>
  void
  assign(Vector_Crtp<V0_IMPL>& v0,
         const _product_t_,
         const _inverse_t_,
         const _matrix_unary_op_t_<OP1> op1,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Vector_Crtp<V1_IMPL>& v1)
  {
  }

}  // namespace LinearAlgebra
