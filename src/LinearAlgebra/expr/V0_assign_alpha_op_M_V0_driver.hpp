//
// V0 = α op(M) V0 (inplace product, triangular matrices)
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
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         Vector_Crtp<V_0_TYPE>& v_0,                                   // v_0 =
         const Common_Element_Type_t<V_0_TYPE, M_TYPE> alpha,          // alpha
         const _matrix_unary_op_t_<M_OP> op,                           // op
         const Matrix_Crtp<M_TYPE>& M,                                 // M
         const _lhs_t_                                                 // lhs
  )
  {
    static_assert(not std::is_same_v<M_TYPE, M_TYPE>, "Not implemented");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE>
  Expr_Selector_Enum
  assign(Vector_Crtp<V_0_TYPE>& v_0,                           // v_0 =
         const Common_Element_Type_t<V_0_TYPE, M_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                   // op
         const Matrix_Crtp<M_TYPE>& M,                         // M
         const _lhs_t_                                         // lhs
  )
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(v_0) ==
           matrix_op(op, dimension_predicate(M)) * dimension_predicate(v_0));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), v_0.impl(), alpha, op, M.impl(), _lhs_);
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
