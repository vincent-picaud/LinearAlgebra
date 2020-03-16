//
// Role:
//
// Compute:
//
// \begin{equation*}
// v_0 = \alpha op(M) v_1 + \beta v_0
// \end{equation*}
//

#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/dimension.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"
#include "LinearAlgebra/meta/always.hpp"
#include "LinearAlgebra/meta/element_type.hpp"

#include "LinearAlgebra/wraps/blas/subroutines.hpp"
#include "LinearAlgebra/wraps/blas/to_cblas_transpose.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  // \begin{equation*}
  // v_0 = \alpha v_0 + \beta op(M) v_1
  // \end{equation*}
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  void expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
            Vector_Crtp<V_0_TYPE>& v_0,                           // v_0
            _assign_t_,                                           // =
            const typename V_0_TYPE::element_type alpha,          // alpha
            _vector_0_t_,                                         // v_0
            _plus_t_,                                             // +
            const typename V_1_TYPE::element_type beta,           // beta
            _matrix_unary_op_t_<M_OP> op,                         // op
            const Matrix_Crtp<M_TYPE>& M,                         // M
            const Vector_Crtp<V_1_TYPE>& v_1)                     // v_1
  {
    static_assert(not std::is_same_v<M_TYPE, M_TYPE>, "Not implemented");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  // \begin{equation*}
  // v_0 = \alpha v_0 + \beta op(M) v_1
  // \end{equation*}
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  void expr(Vector_Crtp<V_0_TYPE>& v_0,                   // v_0
            _assign_t_,                                   // =
            const typename V_0_TYPE::element_type alpha,  // alpha
            _vector_0_t_,                                 // v_0
            _plus_t_,                                     // +
            const typename V_1_TYPE::element_type beta,   // beta
            _matrix_unary_op_t_<M_OP> op,                 // op
            const Matrix_Crtp<M_TYPE>& M,                 // M
            const Vector_Crtp<V_1_TYPE>& v_1)             // v_1
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op, dimension_predicate(M)) * dimension_predicate(v_1) +
           dimension_predicate(v_0));

    // Delegate computation
    //
    expr(Expr_Selector<>(), v_0.impl(), _assign_, alpha, _vector_0_, _plus_, beta, op, M.impl(),
         v_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from:
  //
  // \begin{equation*}
  // v_0 = \alpha op(M) v_1 + \beta v_0
  // \end{equation*}
  //
  // to:
  //
  // \begin{equation*}
  // v_0 = \beta v_0 + \alpha op(M) v_1
  // \end{equation*}
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum OP_M, typename M_TYPE,
            typename V_1_TYPE>
  void
  expr(Vector_Crtp<V_0_TYPE>& v_0,           // v_0
       _assign_t_,                           // =
       const Element_Type_t<M_TYPE>& alpha,  // α
       const _matrix_unary_op_t_<OP_M> op,   // op
       const Matrix_Crtp<M_TYPE>& M,         // M
       const Vector_Crtp<V_1_TYPE>& v_1,     // v_1
       const _plus_t_,                       // +
       const Element_Type_t<M_TYPE>& beta,   // β
       const _vector_0_t_                    // v_0

  )
  {
    expr(v_0, _assign_, beta, _vector_0_, _plus_, alpha, op, M, v_1);
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //
  //  Implementation: CBlas
  //
#if (HAS_BLAS)
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum OP_M, typename M_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Blas>,
       Default_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Element_Type_t<M_TYPE> alpha,       // α
       const _vector_0_t_,                       // v_0
       const _plus_t_,                           // +
       const Element_Type_t<M_TYPE> beta,        // β
       const _matrix_unary_op_t_<OP_M>,          // op
       const Default_Matrix_Crtp<M_TYPE>& M,     // M
       const Default_Vector_Crtp<V_1_TYPE>& v_1  // v_1
       )
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<OP_M> &&
          // Blas function availability?
          Always_True_v<decltype(Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<OP_M>,
                                            M.I_size(), M.J_size(), alpha, M.data(),
                                            M.leading_dimension(), v_1.data(), v_1.increment(),
                                            beta, v_0.data(), v_0.increment()))> &&
          // Generic matrix
          (M_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None)>
  {
    Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<OP_M>, M.I_size(), M.J_size(), alpha,
               M.data(), M.leading_dimension(), v_1.data(), v_1.increment(), beta, v_0.data(),
               v_0.increment());
  }
#endif
}
