//
// M0=αop(M1)op(M2)+βM0   M0=lhs
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/expr/scalar_crtp.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  // // [BEGIN_assign]
  // // *User interface*
  // // \begin{equation*}
  // // M_0 = \alpha * op_1(M_1) * op_2(M_2) + \beta * M_3
  // // \end{equation*}
  // //
  // // Reverse polish:
  // // \begin{equation*}
  // // M_0 = +\ *\ *\ \alpha\ op_1\ M_1\ op_2\ M_2\ *\ \beta\ M_3
  // // \end{equation*}
  // //
  // //
  // //
  // template <typename M0_IMPL,
  //           typename ALPHA_IMPL,
  //           Matrix_Unary_Op_Enum OP1,
  //           typename M1_IMPL,
  //           Matrix_Unary_Op_Enum OP2,
  //           typename M2_IMPL,
  //           typename BETA_IMPL,
  //           typename M3_IMPL>
  // void
  // assign(Matrix_Crtp<M0_IMPL>& M0,
  //        const _plus_t_,
  //        const _product_t_,
  //        const _product_t_,
  //        const Scalar_Crtp<ALPHA_IMPL>& alpha,
  //        const _matrix_unary_op_t_<OP1> op1,
  //        const Matrix_Crtp<M1_IMPL>& M1,
  //        const _matrix_unary_op_t_<OP2> op2,
  //        const Matrix_Crtp<M2_IMPL>& M2,
  //        const _product_t_,
  //        const Scalar_Crtp<BETA_IMPL>& beta,
  //        const Matrix_Crtp<M3_IMPL>& M3)
  // {
  //   // Here is the right place to check dimension once for all.
  //   //
  //   assert(dimension_predicate(M0.impl()) = matrix_op(op1, dimension_predicate(M1.impl())) *
  //                                               matrix_op(op2, dimension_predicate(M2.impl())) +
  //                                           dimension_predicate(M3.impl()));

  //   // Delegate computation
  //   //
  //   assign(Expr_Selector<>(),
  //          M0.impl(),
  //          _plus_,
  //          _product_,
  //          _product_,
  //          alpha,
  //          op1,
  //          M1.impl(),
  //          op2,
  //          M2.impl(),
  //          _product_,
  //          beta,
  //          M3.impl());
  // }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //
  //
  // CAVEAT: as it use _lhs_t_, thus cannot be called from metaExpr, it
  //         is useless to define any alias
  //
}  // namespace LinearAlgebra
