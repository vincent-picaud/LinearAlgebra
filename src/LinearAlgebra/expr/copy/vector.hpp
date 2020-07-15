#pragma once

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"
#include "LinearAlgebra/expr/copy/generic.hpp"

namespace LinearAlgebra
{
  // ////////////////////////////////////////////////////////////////
  //  Generic Implementation
  // ////////////////////////////////////////////////////////////////
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Vector_Crtp<V0_IMPL>& v0,
         const Vector_Crtp<V1_IMPL>& v1)
      -> std::enable_if_t<Always_True_v<decltype(Detail::generic_copy(v0.impl(), v1.impl()))>>
  {
    assert(dimension_predicate(v0.impl()) == dimension_predicate(v1.impl()));

    Detail::generic_copy(v0.impl(), v1.impl());

    DEBUG_SET_SELECTED(selected);
  }

  // ////////////////////////////////////////////////////////////////
  //  Blas Implementation
  // ////////////////////////////////////////////////////////////////
  //
#if (HAS_BLAS)
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Vector_Crtp<V0_IMPL>& v0,
         const Vector_Crtp<V1_IMPL>& v1)
      -> std::enable_if_t<
          Always_True_v<decltype(Blas::copy(v1.impl(), v0.impl()))>>  //  CAVEAT: and not Blas::copy(v0, v1)
  {
    assert(are_compatible_p(v0.impl(), v1.impl()));

    Blas::copy(v1.impl(), v0.impl());

    DEBUG_SET_SELECTED(selected);
  }
#endif

  // ////////////////////////////////////////////////////////////////
  //  Static Implementation
  // ////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  // Role: skip Blas when dimension are static
  //
  template <typename V0_IMPL, typename V1_IMPL>
  std::enable_if_t<Any_Has_Static_Dimension_v<V0_IMPL, V1_IMPL>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Vector_Crtp<V0_IMPL>& v0,
         const Vector_Crtp<V1_IMPL>& v1)
  {
    assign(Expr_Selector<Expr_Selector_Enum::Generic>{}, v0, v1);

    DEBUG_SET_SELECTED(selected);
  }
}  // namespace LinearAlgebra
