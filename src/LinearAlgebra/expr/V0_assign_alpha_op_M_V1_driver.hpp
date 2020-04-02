//
// V0 = α op(M) V1
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
         const Common_Element_Type_t<V0_TYPE, M_TYPE> alpha,           // alpha
         const _matrix_unary_op_t_<M_OP> op,                           // op
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
  assign(Vector_Crtp<V0_TYPE>& v0,                            // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                  // op
         const Matrix_Crtp<M_TYPE>& M,                        // M
         const Vector_Crtp<V1_TYPE>& v1                       // v1
  )
  {
    // Here is the right place to check dimension once for all.
    //
    assert(dimension_predicate(v0) ==
           matrix_op(op, dimension_predicate(M)) * dimension_predicate(v0));

    // Delegate computation
    //
    return assign(Expr_Selector<>(), v0.impl(), alpha, op, M.impl(), v1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //
}
