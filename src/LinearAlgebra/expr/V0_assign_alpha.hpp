//
// Compute: V = alpha
//
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

// specific includes
#include "LinearAlgebra/dense/vector_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  static inline auto
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         Vector_Crtp<IMPL>& vector_0,                                  // vector_0
         const typename IMPL::element_type scalar)                     // scalar
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  static inline auto
  assign(Vector_Crtp<IMPL>& vector_0,               // vector_0
         const typename IMPL::element_type scalar)  // scalar
  {
    return assign(Expr_Selector<>(), vector_0.impl(), scalar);
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
  static inline auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,  // Generic implementation
         Dense_Vector_Crtp<IMPL>& vector_0,                          // vector_0
         const typename IMPL::element_type scalar)                   // scalar

  {
    fill([scalar]() { return scalar; }, vector_0);
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
  template <typename IMPL>
  static inline std::enable_if_t<Any_Has_Static_Size_v<IMPL>,
                                 Expr_Selector<Expr_Selector_Enum::Static>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,  // Generic implementation
         Dense_Vector_Crtp<IMPL>& vector_0,                         // vector_0
         const typename IMPL::element_type scalar)                  // scalar

  {
    // Directly jump to generic implementation that takes into account
    // static size without taking the risk of being catch by the BLAS
    // like specializations
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), vector_0, scalar);
    return selected;
  }
}
