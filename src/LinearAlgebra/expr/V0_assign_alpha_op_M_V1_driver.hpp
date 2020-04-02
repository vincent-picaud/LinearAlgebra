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
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                           // op
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    static_assert(not std::is_same_v<M_TYPE, M_TYPE>, "Not implemented");
    return selected;
  }
  // inverse
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                           // op
         const _inverse_t_,                                            // inverse
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    static_assert(not std::is_same_v<M_TYPE, M_TYPE>, "Not implemented");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                           // op
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(v0) ==
           matrix_op(op, dimension_predicate(M)) * dimension_predicate(v1));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), v0.impl(), alpha, op, M.impl(), v1.impl());
  }
  // inverse
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                           // op
         const _inverse_t_,                                            // inverse
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    // Here is the right place to check dimension once for all.
    //
    assert(M.I_size() == M.J_size());  // inverse => square
    assert(dimension_predicate(v0) ==
           matrix_op(op, dimension_predicate(M)) * dimension_predicate(v1));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), v0.impl(), alpha, op, _inverse_, M.impl(), v1.impl());
  }
  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  // V0 = M V1
  //
  template <typename V0_TYPE, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,       // v0 =
         const Matrix_Crtp<M_TYPE>& M,   // M
         const Vector_Crtp<V1_TYPE>& v1  // v1
  )
  {
    return assign(v0.impl(), 1, _identity_, M.impl(), v1.impl());
  }
  //
  // V0 = inverse(M) V1
  //
  template <typename V0_TYPE, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,       // v0 =
         const _inverse_t_,              // inverse
         const Matrix_Crtp<M_TYPE>& M,   // M
         const Vector_Crtp<V1_TYPE>& v1  // v1
  )
  {
    return assign(v0.impl(), 1, _identity_, _inverse_, M.impl(), v1.impl());
  }

  //
  // V0 = α M V1
  //
  template <typename V0_TYPE, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    return assign(v0.impl(), alpha, _identity_, M.impl(), v1.impl());
  }
  //
  // V0 = α inverse(M) V1
  //
  template <typename V0_TYPE, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const _inverse_t_,                                            // inverse
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    return assign(v0.impl(), alpha, _identity_, _inverse_, M.impl(), v1.impl());
  }

  //
  // V0 = op(M) V1
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,            // v0 =
         const _matrix_unary_op_t_<M_OP> op,  // op
         const Matrix_Crtp<M_TYPE>& M,        // M
         const Vector_Crtp<V1_TYPE>& v1       // v1
  )
  {
    return assign(Expr_Selector<>(), v0.impl(), 1, op, M.impl(), v1.impl());
  }
  //
  // V0 = inverse(op(M)) V1
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,            // v0 =
         const _inverse_t_,                   // inverse
         const _matrix_unary_op_t_<M_OP> op,  // op
         const Matrix_Crtp<M_TYPE>& M,        // M
         const Vector_Crtp<V1_TYPE>& v1       // v1
  )
  {
    return assign(Expr_Selector<>(), v0.impl(), 1, op, _inverse_, M.impl(), v1.impl());
  }
  //
  // V0 = op(inverse(M) V1
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,            // v0 =
         const _matrix_unary_op_t_<M_OP> op,  // op
         const _inverse_t_,                   // inverse
         const Matrix_Crtp<M_TYPE>& M,        // M
         const Vector_Crtp<V1_TYPE>& v1       // v1
  )
  {
    return assign(Expr_Selector<>(), v0.impl(), 1, op, _inverse_, M.impl(), v1.impl());
  }
  //
  // V0 = α inverse(op(M)) V1
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V1_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V0_TYPE>& v0,                                     // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE, V1_TYPE> alpha,  // alpha
         const _inverse_t_,                                            // inverse
         const _matrix_unary_op_t_<M_OP> op,                           // op
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const Vector_Crtp<V1_TYPE>& v1                                // v1
  )
  {
    return assign(Expr_Selector<>(), v0.impl(), alpha, op, _inverse_, M.impl(), v1.impl());
   }
}
