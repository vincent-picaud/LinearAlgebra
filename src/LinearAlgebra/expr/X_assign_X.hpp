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

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_are_compatible.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_transform.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

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
       _assign_t_,                             // =
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
       _assign_t_,                             // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
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
       _assign_t_,                             // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
    // v0 is unused, but the advantage is that transform checks for
    // possible static size in both v0 & v1
    transform(
        [](const auto v0_i, const auto v1_i) {
          (void)v0_i;
          return v1_i;
        },
        v_0, v_1);

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
       _assign_t_,                             // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
       )
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(v_0.size(), v_1.data(), v_1.increment(),
                                                            v_0.data(), v_0.increment()))>,
                          std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Blas>>
  {
    assert(are_compatible_p(v_0, v_1));

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
       _assign_t_,                             // =
       const Dense_Vector_Crtp<V_1_TYPE>& v_1  // v_1
       ) -> std::enable_if_t<Any_Has_Static_Size_v<V_0_TYPE, V_1_TYPE>,
                             std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Static>>

  {
    // v0 is unused, but the advantage is that transform checks for
    // possible static size in both v0 & v1
    expr(Expr_Selector<Expr_Selector_Enum::Generic>(), v_0.impl(), _assign_, v_1.impl());

    return {};
  }
}
