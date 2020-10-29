#pragma once

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_fwd.hpp"
#include "LinearAlgebra/expr/X0_eq_aX1_X2/generic.hpp"
#include "LinearAlgebra/expr/copy.hpp"
#include "LinearAlgebra/expr/expr.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Generic
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename ALPHA_IMPL, typename V1_IMPL, typename V2_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
      -> std::enable_if_t<Always_True_v<
          decltype(Detail::generic_X0_eq_aX1_X2(v0.impl(), alpha.impl(), v1.impl(), v2.impl()))>>
  {
    Detail::generic_X0_eq_aX1_X2(v0.impl(), alpha.impl(), v1.impl(), v2.impl());

    DEBUG_SET_SELECTED(selected);
  }

//////////////////////////////////////////////////////////////////
// Blas
//////////////////////////////////////////////////////////////////
// TODO missing axpy
#if (HAS_BLAS)
  // template <typename V0_IMPL, typename ALPHA_IMPL, typename V1_IMPL, typename V2_IMPL>
  // auto
  // assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
  //        Vector_Crtp<V0_IMPL>& v0,
  //        const _plus_t_,
  //        const _product_t_,
  //        const Scalar_Crtp<ALPHA_IMPL>& alpha,
  //        const Vector_Crtp<V1_IMPL>& v1,
  //        const Vector_Crtp<V2_IMPL>& v2)
  //     -> std::enable_if_t<Always_True_v<decltype(assign(v0.impl(), v2.impl()))> and
  //                         Always_True_v<decltype(Blas::scal(alpha.value(), v0.impl()))>>

  // {
  //   assert(dimension_predicate(v0.impl()) == dimension_predicate(v1.impl()));

  //   if (not same_mathematical_object_p(v0, v1))
  //   {
  //     assign(v0.impl(), v1.impl());
  //   }
  //   Blas::scal(alpha.value(), v0.impl());

  //   DEBUG_SET_SELECTED(selected);
  // }
#endif

  //////////////////////////////////////////////////////////////////
  // Static
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename ALPHA_IMPL, typename V1_IMPL, typename V2_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Vector_Crtp<V0_IMPL>& v0,
         const _plus_t_,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Vector_Crtp<V1_IMPL>& v1,
         const Vector_Crtp<V2_IMPL>& v2)
      -> std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL, V2_IMPL>>
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>{},
           v0.impl(),
           _plus_,
           _product_,
           alpha.impl(),
           v1.impl(),
           v2.impl());

    DEBUG_SET_SELECTED(selected);
  }

}  // namespace LinearAlgebra
