//
// CAVEAT: we follow BLAS convention conjugate(x)^t.y (and NOT x^t.conjugate(y))
//
#pragma once

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_scan.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/complex.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/has_static_dimension.hpp"

namespace LinearAlgebra::Detail
{
#ifndef NDEBUG
  Expr_Selector_Enum utest_selected;
#define DEBUG_RESET_SELECTED() LinearAlgebra::Detail::utest_selected = Expr_Selector_Enum::END
#define DEBUG_GET_SELECTED() (LinearAlgebra::Detail::utest_selected)
#define DEBUG_SET_SELECTED(value) LinearAlgebra::Detail::utest_selected = (value)

#else

#define DEBUG_RESET_SELECTED()
#define DEBUG_GET_SELECTED()
#define DEBUG_SET_SELECTED(value)

#endif
}

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename V1_IMPL>
  void
  dot(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  //
      const Dense_Vector_Crtp<V0_IMPL>& V0,                 //
      const Dense_Vector_Crtp<V1_IMPL>& V1                  //
  )
  {
    static_assert(Always_False_v<V0_IMPL>, "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  dot(const Dense_Vector_Crtp<V0_IMPL>& V0,  //
      const Dense_Vector_Crtp<V1_IMPL>& V1   //
  )
  {
    return dot(Expr_Selector<>(), V0.impl(), V1.impl());
  }

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
  dot(const Expr_Selector<Expr_Selector_Enum::Generic>&,  //
      const Dense_Vector_Crtp<V0_IMPL>& V0,               //
      const Dense_Vector_Crtp<V1_IMPL>& V1                //
  )
  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Generic);

    Common_Element_Type_t<V0_IMPL, V1_IMPL> sum{0};

    if constexpr (Is_Complex_v<Element_Type_t<V0_IMPL>>)
    {
      scan([&sum](const auto& v0_component,
                  const auto& v1_component) { sum += conjugate(v0_component) * v1_component; },
           V0, V1);
    }
    else
    {
      scan([&sum](const auto& v0_component,
                  const auto& v1_component) { sum += v0_component * v1_component; },
           V0, V1);
    }
    return sum;
  }

  //================================================================
  //  Implementation: Blas
  //================================================================
  //
#if (HAS_BLAS)
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  dot(const Expr_Selector<Expr_Selector_Enum::Blas>&,  //
      const Dense_Vector_Crtp<V0_IMPL>& V0,            //
      const Dense_Vector_Crtp<V1_IMPL>& V1             //
      ) -> decltype(Blas::dot(V0.size(), V0.data(), V0.increment(), V1.data(), V1.increment()))

  {
    assert(dimension_predicate(V0) == dimension_predicate(V1));

    DEBUG_SET_SELECTED(Expr_Selector_Enum::Blas);
    
    return Blas::dot(V0.size(), V0.data(), V0.increment(), V1.data(), V1.increment());
  }
#endif

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  dot(const Expr_Selector<Expr_Selector_Enum::Static>&,  //
      const Dense_Vector_Crtp<V0_IMPL>& V0,              //
      const Dense_Vector_Crtp<V1_IMPL>& V1               //
      ) -> std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL>,
                            decltype(dot(Expr_Selector<Expr_Selector_Enum::Generic>(), V0.impl(),
                                         V1.impl()))>

  {
    DEBUG_SET_SELECTED(Expr_Selector_Enum::Static);

    return dot(Expr_Selector<Expr_Selector_Enum::Generic>(), V0.impl(), V1.impl());
  }
}
