//
// CAVEAT: in order to avoid confusion between alpha, beta it is better to stick to blas conventions:
//
// v_0 = \alpha op(M) v_1 + \beta v_0
//

#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/dimension.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"

#include "LinearAlgebra/meta/all_same_type.hpp"
#include "LinearAlgebra/meta/always.hpp"
#include "LinearAlgebra/meta/element_type.hpp"

#include "LinearAlgebra/wraps/blas/blas.hpp"

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
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,            // Undefined implementation
       Vector_Crtp<V_0_TYPE>& v_0,                                     // v_0
       _assign_t_,                                                     // =
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
       _matrix_unary_op_t_<M_OP> op,                                   // op
       const Matrix_Crtp<M_TYPE>& M,                                   // M
       const Vector_Crtp<V_1_TYPE>& v_1,                               // v_1
       _plus_t_,                                                       // +
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
       _vector_0_t_)                                                   // v_0
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
  auto
  expr(Vector_Crtp<V_0_TYPE>& v_0,  // v_0
       _assign_t_,                  // =
       // const typename V_0_TYPE::element_type alpha,
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
       _matrix_unary_op_t_<M_OP> op,                                   // op
       const Matrix_Crtp<M_TYPE>& M,                                   // M
       const Vector_Crtp<V_1_TYPE>& v_1,                               // v_1
       _plus_t_,                                                       // +
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
       _vector_0_t_)                                                   // v_0
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op, dimension_predicate(M)) * dimension_predicate(v_1) +
           dimension_predicate(v_0));

    // Delegate computation
    //
    return expr(Expr_Selector<>(), v_0.impl(), _assign_, alpha, op, M.impl(), v_1.impl(), _plus_,
                beta, _vector_0_);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  //
  // v_0 = \beta v_0 + \alpha op(M) v_1
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE,
            typename V_1_TYPE>
  auto
  expr(Vector_Crtp<V_0_TYPE>& v_0,                                      // v_0
       _assign_t_,                                                      // =
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE>& beta,   // β
       const _vector_0_t_,                                              // v_0,
       const _plus_t_,                                                  // +
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE>& alpha,  // α
       const _matrix_unary_op_t_<M_OP> op,                              // op
       const Matrix_Crtp<M_TYPE>& M,                                    // M
       const Vector_Crtp<V_1_TYPE>& v_1)                                // v_1
  {
    //assert(0);

    return expr(v_0, _assign_, alpha, op, M, v_1, _plus_, beta, _vector_0_);
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //
  //  Implementation: CBlas
  //
#if (HAS_BLAS)
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Blas>,
       Dense_Vector_Crtp<V_0_TYPE>& v_0,                             // v_0
       _assign_t_,                                                     // =
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
       _matrix_unary_op_t_<M_OP> op,                                   // op
       const Dense_Matrix_Crtp<M_TYPE>& M,                           // M
       const Dense_Vector_Crtp<V_1_TYPE>& v_1,                       // v_1
       _plus_t_,                                                       // +
       const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
       _vector_0_t_)                                                   // v_0

      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<M_OP> &&
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<M_TYPE>, Element_Type_t<V_0_TYPE>,
                              Element_Type_t<V_1_TYPE>> &&
              // Scalar support
              Is_CBlas_Supported_Scalar_v<Element_Type_t<M_TYPE>> &&
              // Generic matrix
              (M_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None),
          std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Blas>>
  {
    Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<M_OP>, M.I_size(), M.J_size(), alpha,
               M.data(), M.leading_dimension(), v_1.data(), v_1.increment(), beta, v_0.data(),
               v_0.increment());
    return {};
  }
#endif
}
