//
// Compute: X0 = alpha X0
//
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

//#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

// specific includes
#include "LinearAlgebra/dense/matrix_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         Matrix_Crtp<IMPL>& matrix_0,                                  // matrix_0
         const typename IMPL::element_type scalar,                     // scalar
         _matrix_0_t_                                                  // matrix_0
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
  assign(Matrix_Crtp<IMPL>& matrix_0,               // matrix_0
         const typename IMPL::element_type scalar,  // scalar
         _matrix_0_t_                               // matrix_0
  )
  {
    return assign(Expr_Selector<>(), matrix_0.impl(), scalar, _matrix_0_);
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
         Dense_Matrix_Crtp<IMPL>& matrix_0,                          // matrix_0
         const typename IMPL::element_type scalar,                   // scalar
         _matrix_0_t_                                                // matrix_0
  )
  {
    transform([scalar](const auto& matrix_0_component) { return scalar * matrix_0_component; },
              matrix_0);

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
