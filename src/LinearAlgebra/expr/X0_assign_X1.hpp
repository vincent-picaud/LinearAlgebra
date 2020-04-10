//
// X0 = X1
//
#pragma once

#include "LinearAlgebra/expr/expr.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/dense/vector_is_same.hpp"

#include "LinearAlgebra/dense/matrix_fill.hpp"
#include "LinearAlgebra/dense/matrix_is_same.hpp"

namespace LinearAlgebra
{

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(VMT_Crtp<X0_TYPE>& X0,       // X0
         const VMT_Crtp<X1_TYPE>& X1  // X1
  )
  {
    // Something to do?
    if (not is_same(X0.impl(), X1.impl()))
    {
      assign(Expr_Selector<>(), X0.impl(), X1.impl());
    }
    else
    {
      DEBUG_SET_SELECTED(Expr_Selector_Enum::END);
    }
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         VMT_Crtp<X0_TYPE>& X0,       // X0
         const VMT_Crtp<X1_TYPE>& X1  // X1
  )
  {
    // Note: "fill()" checks for possible static size in both X0 &
    // X1
    fill([](const auto X1_component) { return X1_component; }, X0.impl(), X1.impl());

    DEBUG_SET_SELECTED(selected);
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename X0_TYPE, typename X1_TYPE>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_TYPE, X1_TYPE>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         VMT_Crtp<X0_TYPE>& X0,       // X0
         const VMT_Crtp<X1_TYPE>& X1  // X1
  )
  {
    // skip blas when X0 or X1 has a static size
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), X0.impl(), X1.impl());

    DEBUG_SET_SELECTED(selected);
  }
}
