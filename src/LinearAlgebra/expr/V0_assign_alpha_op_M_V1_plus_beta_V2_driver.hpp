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
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE,
            typename V2_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Vector_Crtp<V0_TYPE>& V0,                                              // V0 =
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, V2_TYPE, M_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                                    // op
         const Matrix_Crtp<M_TYPE>& M,                                          // M
         const Vector_Crtp<V1_TYPE>& V1,                                        // V1
         const _plus_t_,                                                        // +
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, V2_TYPE, M_TYPE> beta,   // beta
         const Vector_Crtp<V2_TYPE>& V2)                                        // V1
  {
    static_assert(not std::is_same_v<M_TYPE, M_TYPE>, "Not implemented");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE,
            typename V2_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& V0,                                              // V0 =
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, V2_TYPE, M_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                                    // op
         const Matrix_Crtp<M_TYPE>& M,                                          // M
         const Vector_Crtp<V1_TYPE>& V1,                                        // V1
         const _plus_t_,                                                        // +
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, V2_TYPE, M_TYPE> beta,   // beta
         const Vector_Crtp<V2_TYPE>& V2)                                        // V1
  {
    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op, dimension_predicate(M)) * dimension_predicate(V1) +
           dimension_predicate(V0));

    // Delegate computation
    //
    assert(0);
    return assign(Expr_Selector<>(), V0.impl(), alpha, op, M.impl(), V1.impl(), _plus_, beta,
                  V2.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  //
  //   V0 = α M V1 + β V2
  //
  template <typename V0_TYPE, typename M_TYPE, typename V1_TYPE,
            typename V2_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& V0,                                              // V0 =
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, V2_TYPE, M_TYPE> alpha,  // alpha
         const Matrix_Crtp<M_TYPE>& M,                                          // M
         const Vector_Crtp<V1_TYPE>& V1,                                        // V1
         const _plus_t_,                                                        // +
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, V2_TYPE, M_TYPE> beta,   // beta
         const Vector_Crtp<V2_TYPE>& V2)                                        // V1
  {
    //    return assign(V0, alpha, _identity_, M, V1, _plus_, beta, V2);
    return Expr_Selector_Enum::Undefined;
  }
  //
  // V0 = β.V2 + α.op(M).V1
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE,
            typename V2_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& V0,                                      // V0 =
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, M_TYPE>& beta,   // β
         const Vector_Crtp<V2_TYPE>& V2,                                // V2,
         const _plus_t_,                                                // +
         const Common_Element_Type_t<V0_TYPE, V1_TYPE, M_TYPE>& alpha,  // α
         const _matrix_unary_op_t_<M_OP> op,                            // op
         const Matrix_Crtp<M_TYPE>& M,                                  // M
         const Vector_Crtp<V1_TYPE>& V1)                                // V1
  {
    return assign(V0, alpha, op, M, V1, _plus_, beta, V2);
  }

}
