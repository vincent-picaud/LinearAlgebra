//
// X0 = X1
//
#pragma once

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

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
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename VMT_0_TYPE, typename VMT_1_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         VMT_Crtp<VMT_0_TYPE>& vmt_0,       // vmt_0
         const VMT_Crtp<VMT_1_TYPE>& vmt_1  // vmt_1
  )
  {
    static_assert(Always_False_v<VMT_0_TYPE>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename VMT_0_TYPE, typename VMT_1_TYPE>
  Expr_Selector_Enum
  assign(VMT_Crtp<VMT_0_TYPE>& vmt_0,       // vmt_0
         const VMT_Crtp<VMT_1_TYPE>& vmt_1  // vmt_1
  )
  {
    // Something to do?
    if (is_same(vmt_0.impl(), vmt_1.impl()))
    {
      return Expr_Selector_Enum::END;
    }

    return assign(Expr_Selector<>(), vmt_0.impl(), vmt_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename VMT_0_TYPE, typename VMT_1_TYPE>
  Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         VMT_Crtp<VMT_0_TYPE>& vmt_0,       // vmt_0
         const VMT_Crtp<VMT_1_TYPE>& vmt_1  // vmt_1
  )
  {
    // Note: "fill()" checks for possible static size in both vmt_0 &
    // vmt_1
    fill([](const auto vmt_1_component) { return vmt_1_component; }, vmt_0.impl(), vmt_1.impl());

    return selected;
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename VMT_0_TYPE, typename VMT_1_TYPE>
  std::enable_if_t<Any_Has_Static_Dimension_v<VMT_0_TYPE, VMT_1_TYPE>, Expr_Selector_Enum>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         VMT_Crtp<VMT_0_TYPE>& VMT_0,       // VMT_0
         const VMT_Crtp<VMT_1_TYPE>& VMT_1  // VMT_1
  )
  {
    // skip blas when vmt_0 or vmt_1 has a static size
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), VMT_0.impl(), VMT_1.impl());

    return selected;
  }
}
