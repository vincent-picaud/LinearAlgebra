//
// M0=αop(M1)op(M2)+βM0   M0=lhs, M2=rhs_1
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_debug.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  struct Undefined_Assign
  {
  };

  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename M0_TYPE, Matrix_Unary_Op_Enum OP1_ENUM, typename M1_TYPE,
            Matrix_Unary_Op_Enum OP2_ENUM>
  Undefined_Assign
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  //
         Matrix_Crtp<M0_TYPE>& M0,                                     //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE> alpha,          //
         const _matrix_unary_op_t_<OP1_ENUM> op1,                      //
         const Matrix_Crtp<M1_TYPE>& M1,                               //
         const _matrix_unary_op_t_<OP2_ENUM> op2,                      //
         const _rhs_1_t_,                                              //
         const _plus_t_,                                               //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE> beta,           //
         const _lhs_t_)                                                //
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Undefined);
    assert(0);
    return {};
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename M0_TYPE, Matrix_Unary_Op_Enum OP1_ENUM, typename M1_TYPE,
            Matrix_Unary_Op_Enum OP2_ENUM>
  void
  assign(Matrix_Crtp<M0_TYPE>& M0,                             //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE> alpha,  //
         const _matrix_unary_op_t_<OP1_ENUM> op1,              //
         const Matrix_Crtp<M1_TYPE>& M1,                       //
         const _matrix_unary_op_t_<OP2_ENUM> op2,              //
         const _rhs_1_t_,                                      //
         const _plus_t_,                                       //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE> beta,   //
         const _lhs_t_)                                        //
  {
    static_assert(
        not std::is_same_v<Undefined_Assign,
                           decltype(assign(Expr_Selector<>(), M0.impl(), alpha, op1, M1.impl(), op2,
                                           _rhs_1_, _plus_, beta, _lhs_))>);

    // Here is the right place to check dimension once for all.
    //
    assert(matrix_op(op1, dimension_predicate(M1.impl())) *
               matrix_op(op2, dimension_predicate(M1.impl())) ==
           dimension_predicate(M0.impl()));

    // Delegate computation
    //
    assign(Expr_Selector<>(), M0.impl(), alpha, op1, M1.impl(), op2, _rhs_1_, _plus_, beta, _lhs_);
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
