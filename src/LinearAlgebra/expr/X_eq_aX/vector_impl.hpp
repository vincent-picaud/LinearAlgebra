#pragma once

#include "LinearAlgebra/expr/copy/generic_interface.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  // X0 = alpha * X0
  // X0 = * alpha X0
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename ALPHA_IMPL, typename X0_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Vector_Crtp<X0_IMPL>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _lhs_t_)
  {
    assign_helper(X0.impl(), _product_, alpha.impl(), _lhs_);

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)
  template <typename ALPHA_IMPL, typename X0_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<X0_IMPL>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _lhs_t_) -> std::enable_if_t<Always_True_v<decltype(Blas::scal(alpha.value(), X0))>>
  {
    Blas::scal(alpha.value(), X0.impl());

    DEBUG_SET_SELECTED(selected);
  }
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  // Role: skip Blas when dimension are static
  //
  template <typename ALPHA_IMPL, typename X0_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Vector_Crtp<X0_IMPL>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const _lhs_t_)
  {
    assign_helper(X0.impl(), _product_, alpha.impl(), _lhs_);

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  // X0 = alpha * X1
  // X0 = * alpha X1
  //
  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Vector_Crtp<X0_IMPL>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Dense_Vector_Crtp<X1_IMPL>& X1)
  {
    assign_helper(X0.impl(), _product_, alpha.impl(), X1.impl());

    DEBUG_SET_SELECTED(selected);
  }
  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<X0_IMPL>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Dense_Vector_Crtp<X1_IMPL>& X1)
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(X1, X0))> and
                          Always_True_v<decltype(Blas::scal(alpha.value(), X0))>>
  {
    Blas::copy(X1, X0);
    Blas::scal(alpha.value(), X0.impl());

    DEBUG_SET_SELECTED(selected);
  }
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  // Role: skip Blas when dimension are static
  //
  template <typename ALPHA_IMPL, typename X0_IMPL, typename X1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_IMPL, X1_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Vector_Crtp<X0_IMPL>& X0,
         const _product_t_,
         const Scalar_Crtp<ALPHA_IMPL>& alpha,
         const Dense_Vector_Crtp<X1_IMPL>& X1)
  {
    assign_helper(X0.impl(), _product_, alpha.impl(), X1.impl());

    DEBUG_SET_SELECTED(selected);
  }
}  // namespace LinearAlgebra
