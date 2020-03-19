//
// Vector copy operations
//

//
// CAVEAT: out argument order convention is not the BLAS one, for instance:
//
//  expr(v0,_assign_,v1)
//
//  but BLAS copy() is:
//
//  copy(n,v1.data(),v1.inc(),v0.data(),v0.inc())
//
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"
#include "LinearAlgebra/meta/always.hpp"
#include "LinearAlgebra/meta/size_utils.hpp"
#include "LinearAlgebra/wraps/blas/blas.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename V_0_TYPE, typename V_1_TYPE>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,
       Dense_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
    static_assert(Always_False_v<V_0_TYPE>, "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename V_0_TYPE, typename V_1_TYPE>
  auto
  expr(Dense_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
    assert(v_0.size() == v_1.size());

    return expr(Expr_Selector<>(), v_0.impl(), _assign_, v_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename V_0_TYPE, typename V_1_TYPE>
  std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Generic>
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,
       Dense_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
    assert(v_0.size() == v_1.size());
    v_0.map_indexed([&](auto& v_0_i, const std::size_t i) { v_0_i = v_1[i]; });
    return {};
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)
  template <typename V_0_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Blas>&,
       Dense_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
       )
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(v_0.size(), v_1.data(), v_1.increment(),
                                                            v_0.data(), v_0.increment()))>,
                          std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Blas>>
  {
    assert(v_0.size() == v_1.size());

    Blas::copy(v_0.size(), v_1.data(), v_1.increment(), v_0.data(), v_0.increment());

    return {};
  }
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename V_0_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Static>&,
       Dense_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
       ) -> std::enable_if_t<Any_Has_Static_Size_v<V_0_TYPE, V_1_TYPE>,
                             std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Static>>

  {
    assert(v_0.size() == v_1.size());
    if constexpr (Has_Static_Size_v<V_0_TYPE>)
    {
      v_0.map_indexed([&](auto& v_0_i, const std::size_t i) { v_0_i = v_1[i]; });
    }
    else
    {
      v_1.map_indexed([&](const auto& v_1_i, const std::size_t i) { v_0[i] = v_1_i; });
    }
    return {};
  }
}
