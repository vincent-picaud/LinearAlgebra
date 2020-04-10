//
// X = alpha
//
#pragma once

#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename ALPHA_IMPL, typename IMPL>
  void
  assign(VMT_Crtp<IMPL>& vmt, const Scalar_Crtp<ALPHA_IMPL>& alpha)
  {
    assign(Expr_Selector<>(), vmt.impl(), alpha.impl());
  }

  // For convenience also support raw scalar type (not do no do that
  // elsewhere as you would also have to define special alias... one
  // for Scalar_Crtp<ALPHA_IMPL> on for Element_t<IMPL>)
  template <typename IMPL>
  void
  assign(VMT_Crtp<IMPL>& vmt, const Element_Type_t<IMPL>& alpha)
  {
    assign(Expr_Selector<>(), vmt.impl(), Scalar_CRef<Element_Type_t<IMPL>>(alpha));
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
  template <typename ALPHA_IMPL, typename IMPL>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected, VMT_Crtp<IMPL>& vmt,
         const Scalar_Crtp<ALPHA_IMPL>& alpha)

  {
    fill([&alpha]() { return alpha.value(); }, vmt.impl());

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename ALPHA_IMPL, typename IMPL>
  static inline std::enable_if_t<Has_Static_Dimension_v<IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected, VMT_Crtp<IMPL>& vmt,
         const Scalar_Crtp<ALPHA_IMPL>& alpha)

  {
    // Directly jump to generic implementation that takes into account
    // static size without taking the risk of being catch by the BLAS
    // like specializations
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), vmt, alpha.impl());

    DEBUG_SET_SELECTED(selected);
  }
}
