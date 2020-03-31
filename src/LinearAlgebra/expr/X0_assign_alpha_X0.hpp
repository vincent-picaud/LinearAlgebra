//
// X0 = α X0
//
#pragma once

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

// specific includes
#include "LinearAlgebra/dense/matrix_transform.hpp"
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
         VMT_Crtp<IMPL>& vmt_0,                                        // vmt_0
         const Element_Type_t<IMPL>& scalar,                           // scalar
         const _lhs_t_                                                 // vmt_0
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
  assign(VMT_Crtp<IMPL>& vmt_0,               // vmt_0
         const Element_Type_t<IMPL>& scalar,  // scalar
         const _lhs_t_                        // vmt_0
  )
  {
    return assign(Expr_Selector<>(), vmt_0.impl(), scalar, _lhs_);
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
         VMT_Crtp<IMPL>& vmt_0,                                      // vmt_0
         const Element_Type_t<IMPL>& scalar,                         // scalar
         const _lhs_t_                                               // vmt_0
  )
  {
    transform([scalar](const auto& vmt_0_component) { return scalar * vmt_0_component; },
              vmt_0.impl());

    return selected;
  }

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,  // Generic implementation
         VMT_Crtp<IMPL>& vmt_0,                                     // vmt_0
         const Element_Type_t<IMPL>& scalar,                        // scalar
         const _lhs_t_                                              // vmt_0
  )
  {
    // Jump over any blas like specialization
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), vmt_0.impl(), scalar, _lhs_);

    return selected;
  }
}
