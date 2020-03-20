//
// Compute: V = alpha
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename V>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Vector_Crtp<V>& v_0,                                  // vector_0
       _assign_t_,                                           // =
       const typename V::element_type scalar)                // scalar
  {
    static_assert(not(std::is_same_v<V, V>), "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename V>
  void
  expr(Vector_Crtp<V>& v_0,                    // vector_0
       _assign_t_,                             // =
       const typename V::element_type scalar)  // scalar
  {
    expr(Expr_Selector<>(), v_0.impl(), _assign_, scalar);
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
  template <typename V_TYPE>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Vector_Crtp<V_TYPE>& v,                       // v
       _assign_t_,                                         // =
       const typename V_TYPE::element_type scalar)         // scalar

  {
    fill([scalar]() { return scalar; }, v);
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
