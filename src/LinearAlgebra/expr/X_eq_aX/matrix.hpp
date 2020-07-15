#pragma once

#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/expr/copy.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"
#include "LinearAlgebra/expr/X_eq_aX/generic.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  // Generic
  // ////////////////////////////////////////////////////////////////
  //
  template <typename M0_IMPL, typename ALPHA_IMPL, typename M1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Matrix_Crtp<M0_IMPL>& M0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& v1)
      -> std::enable_if_t<
          Always_True_v<decltype(Detail::generic_X_eq_aX(M0.impl(), alpha.impl(), v1.impl()))>>
  {
    Detail::generic_X_eq_aX(M0.impl(), alpha.impl(), v1.impl());

    DEBUG_SET_SELECTED(selected);
  }

  // ////////////////////////////////////////////////////////////////
  // Static
  // ////////////////////////////////////////////////////////////////
  //
  template <typename M0_IMPL, typename ALPHA_IMPL, typename M1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Matrix_Crtp<M0_IMPL>& M0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Matrix_Crtp<M1_IMPL>& v1)
      -> std::enable_if_t<
          Any_Has_Static_Dimension_v<M0_IMPL, M1_IMPL> and
          Always_True_v<decltype(Detail::generic_X_eq_aX(M0.impl(), alpha.impl(), v1.impl()))>>
  {
    Detail::generic_X_eq_aX(M0.impl(), alpha.impl(), v1.impl());

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra
