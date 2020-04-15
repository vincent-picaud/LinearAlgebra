#pragma once

#include "LinearAlgebra/scalar_functions/dist_2.hpp"
#include "LinearAlgebra/scalar_functions/norm_2.hpp"

#include "LinearAlgebra/dense/vector_scan.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

#include <cmath>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  squared_dist_2(const Expr_Selector<Expr_Selector_Enum::Generic>,  //
                 const Dense_Vector_Crtp<V0_IMPL>& V0,              //
                 const Dense_Vector_Crtp<V1_IMPL>& V1               //
  )
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Generic);

    decltype(squared_norm_2(V0[0] - V1[0])) sum;
    sum = 0;

    scan([&sum](const auto& v0_component,
                const auto& v1_component) { sum += squared_norm_2(v0_component - v1_component); },
         V0.impl(), V1.impl());

    return sum;
  }
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  dist_2(const Expr_Selector<Expr_Selector_Enum::Generic>,  //
         const Dense_Vector_Crtp<V0_IMPL>& V0,              //
         const Dense_Vector_Crtp<V1_IMPL>& V1               //
  )
  {
    using std::sqrt;

    return sqrt(squared_dist_2(V0.impl(), V1.impl()));
  }

  //================================================================
  //  Implementation: Blas
  //================================================================
  //
  // Not available
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  dist_2(const Expr_Selector<Expr_Selector_Enum::Static>,  //
         const Dense_Vector_Crtp<V0_IMPL>& V0,             //
         const Dense_Vector_Crtp<V1_IMPL>& V1              //
         ) -> std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL>,
                               decltype(dist_2(Expr_Selector<Expr_Selector_Enum::Generic>(),
                                               V0.impl(), V1.impl()))>

  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Static);

    return dist_2(Expr_Selector<Expr_Selector_Enum::Generic>(), V0.impl(), V1.impl());
  }

  template <typename V0_IMPL, typename V1_IMPL>
  auto
  squared_dist_2(const Expr_Selector<Expr_Selector_Enum::Static>,  //
                 const Dense_Vector_Crtp<V0_IMPL>& V0,             //
                 const Dense_Vector_Crtp<V1_IMPL>& V1              //
                 )
      -> std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL>,
                          decltype(squared_dist_2(Expr_Selector<Expr_Selector_Enum::Generic>(),
                                                  V0.impl(), V1.impl()))>

  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Static);

    return squared_dist_2(Expr_Selector<Expr_Selector_Enum::Generic>(), V0.impl(), V1.impl());
  }
}
