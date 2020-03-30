//
// X = alpha
//
#pragma once

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/dense/matrix_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  static inline auto
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  // Undefined implementation
         VMT_Crtp<IMPL>& vmt,                                          // vmt
         const Element_Type_t<IMPL>& scalar)                           // scalar
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
  assign(VMT_Crtp<IMPL>& vmt,                 // vmt
         const Element_Type_t<IMPL>& scalar)  // scalar
  {
    return assign(Expr_Selector<>(), vmt.impl(), scalar);
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
         VMT_Crtp<IMPL>& vmt,                                        // vmt
         const Element_Type_t<IMPL>& scalar)                         // scalar

  {
    fill([scalar]() { return scalar; }, vmt.impl());
    return selected;
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename IMPL>
  static inline std::enable_if_t<Has_Static_Dimension_v<IMPL>,
                                 Expr_Selector<Expr_Selector_Enum::Static>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,  // Generic implementation
         VMT_Crtp<IMPL>& vmt,                                       // vmt
         const typename IMPL::element_type scalar)                  // scalar

  {
    // Directly jump to generic implementation that takes into account
    // static size without taking the risk of being catch by the BLAS
    // like specializations
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), vmt, scalar);
    return selected;
  }
}
