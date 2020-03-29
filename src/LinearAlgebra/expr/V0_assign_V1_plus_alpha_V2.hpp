//
// Compute: X0 = X1 + α X2
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
#include "LinearAlgebra/expr/V0_assign_alpha_V1.hpp"

#include "LinearAlgebra/dense/vector_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0_IMPL, typename VECTOR_1_IMPL, typename VECTOR_2_IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,  //
         const Vector_Crtp<VECTOR_0_IMPL>& vector_0,                   // vector_0
         Vector_Crtp<VECTOR_1_IMPL>& vector_1,                         // vector_1
         _plus_t_,                                                     // +
         const Common_Element_Type_t<VECTOR_0_IMPL,                    //
                                     VECTOR_1_IMPL,                    //
                                     VECTOR_2_IMPL>                    //
             alpha,                                                    // alpha
         const Vector_Crtp<VECTOR_2_IMPL>& vector_2                    // vector_2
  )
  {
    static_assert(Always_False_v<VECTOR_0_IMPL>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0_IMPL, typename VECTOR_1_IMPL, typename VECTOR_2_IMPL>
  static inline Expr_Selector_Enum
  assign(Vector_Crtp<VECTOR_0_IMPL>& vector_0,        // vector_0
         const Vector_Crtp<VECTOR_1_IMPL>& vector_1,  // vector_1
         _plus_t_,                                    // +
         const Common_Element_Type_t<VECTOR_0_IMPL,   //
                                     VECTOR_1_IMPL,   //
                                     VECTOR_2_IMPL>   //
             alpha,                                   // alpha
         const Vector_Crtp<VECTOR_2_IMPL>& vector_2   // vector_2
  )
  {
    return assign(Expr_Selector<>(), vector_0.impl(), vector_1.impl(), _plus_, alpha,
                  vector_2.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Alias
  //////////////////////////////////////////////////////////////////
  //

  // from: X0 = X1   + α X2
  // to  : X0 = α X2 +   X1
  //
  // TODO

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename VECTOR_0_IMPL, typename VECTOR_1_IMPL, typename VECTOR_2_IMPL>
  static inline Expr_Selector_Enum
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,  //
         Vector_Crtp<VECTOR_0_IMPL>& vector_0,                       // vector_0
         const Vector_Crtp<VECTOR_1_IMPL>& vector_1,                 // vector_1
         _plus_t_,                                                   // +
         const Common_Element_Type_t<VECTOR_0_IMPL,                  //
                                     VECTOR_1_IMPL,                  //
                                     VECTOR_2_IMPL>                  //
             alpha,                                                  // alpha
         const Vector_Crtp<VECTOR_2_IMPL>& vector_2                  // vector_2
  )
  {
    transform([&](const auto,                     //
                  const auto vector_1_component,  //
                  const auto vector_2_component   //
              ) { return vector_1_component + alpha * vector_2_component; },
              vector_0.impl(), vector_1.impl(), vector_2.impl());

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
