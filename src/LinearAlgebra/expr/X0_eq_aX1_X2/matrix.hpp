#pragma once

#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/expr/X0_eq_aX1_X2/generic.hpp"
#include "LinearAlgebra/expr/copy.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  // Generic
  // ////////////////////////////////////////////////////////////////
  //
  template <typename M0_IMPL, typename ALPHA_IMPL, typename M1_IMPL, typename M2_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Matrix_Crtp<M0_IMPL>& M0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Matrix_Crtp<M2_IMPL>& M2)
      -> std::enable_if_t<Always_True_v<
          decltype(Detail::generic_X0_eq_aX1_X2(M0.impl(), alpha.impl(), M1.impl(), M2.impl()))>>
  {
    Detail::generic_X0_eq_aX1_X2(M0.impl(), alpha.impl(), M1.impl(), M2.impl());

    DEBUG_SET_SELECTED(selected);
  }

  // ////////////////////////////////////////////////////////////////
  // Blas
  // ////////////////////////////////////////////////////////////////

  // ////////////////////////////////////////////////////////////////
  // Static
  // ////////////////////////////////////////////////////////////////
  //
  template <typename M0_IMPL, typename ALPHA_IMPL, typename M1_IMPL, typename M2_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Matrix_Crtp<M0_IMPL>& M0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& M1,
         const Matrix_Crtp<M2_IMPL>& M2)
      -> std::enable_if_t<Any_Has_Static_Dimension_v<M0_IMPL, M1_IMPL, M2_IMPL>>
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>{},
           M0.impl(),
           _plus_,
           _product_,
           alpha.impl(),
           M1.impl(),
           M2.impl());

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra
