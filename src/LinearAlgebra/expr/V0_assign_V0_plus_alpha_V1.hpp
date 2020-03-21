//
// Compute: V0 = V0 + α V1 (Blas axpy)
//

#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0_IMPL, typename VECTOR_1_IMPL>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Vector_Crtp<VECTOR_0_IMPL>& vector_0,                 // vector_0
       _assign_t_,                                           // =
       _vector_0_t_,                                         // vector_0
       _plus_t_,                                             // +
       const typename VECTOR_0_IMPL::element_type alpha,     // alpha
       const Vector_Crtp<VECTOR_1_IMPL>& vector_1            // vector_1
  )
  {
    static_assert(Always_False_v<VECTOR_0_IMPL>, "Undefined implementation");
    return Expr_Selector_Enum::Undefined;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0_IMPL, typename VECTOR_1_IMPL>
  Expr_Selector_Enum
  expr(Vector_Crtp<VECTOR_0_IMPL>& vector_0,              // vector_0
       _assign_t_,                                        // =
       _vector_0_t_,                                      // vector_0
       _plus_t_,                                          // +
       const typename VECTOR_0_IMPL::element_type alpha,  // alpha
       const Vector_Crtp<VECTOR_1_IMPL>& vector_1         // vector_1
  )
  {
    return expr(Expr_Selector<>(), vector_0.impl(), _assign_, _vector_0_, _plus_, alpha,
                vector_1.impl());
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
  template <typename V_0, typename V_1>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Vector_Crtp<V_0>& v_0,                        // vector_0
       _assign_t_,                                         // =
       _vector_0_t_,                                       // vector_0
       _plus_t_,                                           // +
       const typename V_1::element_type alpha,             // alpha
       const Dense_Vector_Crtp<V_1>& v_1                   // vector_1
  )
  {
    assert(are_compatible_p(v_0.storage_scheme(), v_1.storage_scheme()));

    if (alpha == 0)
    {
      return Expr_Selector_Enum::Generic;  // nothing to do
    }

    if ((void*)&v_0 == (void*)&v_1)
    {
      return expr(v_0, _assign_, 1 + alpha, _vector_0_);
    }

    if (alpha == 1)
    {
      transform([](const auto v0_i, const auto v1_i) { return v0_i + v1_i; }, v_0, v_1);
    }
    else if (alpha == -1)
    {
      transform([](const auto v0_i, const auto v1_i) { return v0_i - v1_i; }, v_0, v_1);
    }
    else
    {
      transform([alpha](const auto v0_i, const auto v1_i) { return v0_i + alpha * v1_i; }, v_0,
                v_1);
    }
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
