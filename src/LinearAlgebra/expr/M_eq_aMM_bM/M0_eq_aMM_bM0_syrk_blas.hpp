#pragma once

#include "LinearAlgebra/expr/M_eq_aMM_bM/M0_eq_aMM_bM0.hpp"

#include "LinearAlgebra/blas/blas.hpp"

namespace LinearAlgebra
{
#if (HAS_BLAS)
  template <typename M0_TYPE, Matrix_Unary_Op_Enum OP1_ENUM, typename M1_TYPE,
            Matrix_Unary_Op_Enum OP2_ENUM, typename M2_TYPE>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,        //
         Matrix_Crtp<M0_TYPE>& M0,                                      //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE, M2_TYPE> alpha,  //
         const _matrix_unary_op_t_<OP1_ENUM> op1,                       //
         const Matrix_Crtp<M1_TYPE>& M1,                                //
         const _matrix_unary_op_t_<OP2_ENUM> op2,                       //
         const Matrix_Crtp<M2_TYPE>& M2,                                //
         const _plus_t_,                                                //
         const Common_Element_Type_t<M0_TYPE, M1_TYPE, M2_TYPE> beta,   //
         const _lhs_t_)                                                 //
  {
    DEBUG_SET_SELECTED(selected);

    assert(0);
  }

#endif
}
