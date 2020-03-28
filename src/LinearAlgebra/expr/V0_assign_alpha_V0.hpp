// Compute: vector_0 = alpha vector_0
//
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

// specific includes
#include "LinearAlgebra/dense/vector_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         Vector_Crtp<IMPL>& vector_0,                                  // vector_0
         const typename IMPL::element_type scalar,                     // scalar
         _vector_0_t_                                                  // vector_0
  )
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  static inline Expr_Selector_Enum
  assign(Vector_Crtp<IMPL>& vector_0,               // vector_0
         const typename IMPL::element_type scalar,  // scalar
         _vector_0_t_                               // vector_0
  )
  {
    return assign(Expr_Selector<>(), vector_0.impl(), scalar, _vector_0_);
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
  //
  template <typename IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,  // Generic implementation
         Dense_Vector_Crtp<IMPL>& vector_0,                          // vector_0
         const typename IMPL::element_type scalar,                   // scalar
         _vector_0_t_                                                // vector_0
  )
  {
    transform([scalar](const auto& vector_0_component) { return scalar * vector_0_component; },
              vector_0);

    return selected;
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
