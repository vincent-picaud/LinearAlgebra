//
// Compute: V = alpha
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Vector_Crtp<IMPL>& vector_0,                          // vector_0
       _assign_t_,                                           // =
       const typename IMPL::element_type scalar)             // scalar
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");
    return Expr_Selector_Enum::Undefined;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  Expr_Selector_Enum
  expr(Vector_Crtp<IMPL>& vector_0,               // vector_0
       _assign_t_,                                // =
       const typename IMPL::element_type scalar)  // scalar
  {
    return expr(Expr_Selector<>(), vector_0.impl(), _assign_, scalar);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from: to:
  //

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename IMPL>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Vector_Crtp<IMPL>& vector_0,                  // vector_0
       _assign_t_,                                         // =
       const typename IMPL::element_type scalar)           // scalar

  {
    fill([scalar]() { return scalar; }, vector_0);
    return Expr_Selector_Enum::Generic;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)

#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
}