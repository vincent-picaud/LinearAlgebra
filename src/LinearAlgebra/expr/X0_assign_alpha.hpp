//
// X = alpha
//
#pragma once

#include "LinearAlgebra/expr/expr_debug.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected, VMT_Crtp<IMPL>& vmt,
         const Element_Type_t<IMPL>& scalar)
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");

    DEBUG_SET_SELECTED(selected);
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  void
  assign(VMT_Crtp<IMPL>& vmt, const Element_Type_t<IMPL>& scalar)
  {
    assign(Expr_Selector<>(), vmt.impl(), scalar);
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
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
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<IMPL>& vmt,
         const Element_Type_t<IMPL>& scalar)

  {
    fill([scalar]() { return scalar; }, vmt.impl());

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename IMPL>
  static inline std::enable_if_t<Has_Static_Dimension_v<IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<IMPL>& vmt,
         const typename IMPL::element_type scalar)

  {
    // Directly jump to generic implementation that takes into account
    // static size without taking the risk of being catch by the BLAS
    // like specializations
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), vmt, scalar);

    DEBUG_SET_SELECTED(selected);
  }
}
