//
// Copy operations vector_0 = vector_1
//
//
// CAVEAT: out argument order convention is not the BLAS one, for instance:
//
//      assign(v0,v1)
//
//  but BLAS copy() is:
//
//      copy(n,v1.data(),v1.inc(),v0.data(),v0.inc())
//
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
#include "LinearAlgebra/dense/vector_is_same.hpp"
#include "LinearAlgebra/dense/vector_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
       Vector_Crtp<VECTOR_0_TYPE>& vector_0,       // vector_0
       const Vector_Crtp<VECTOR_1_TYPE>& vector_1  // vector_1
  )
  {
    static_assert(Always_False_v<VECTOR_0_TYPE>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  auto
  assign(Vector_Crtp<VECTOR_0_TYPE>& vector_0,       // vector_0
       const Vector_Crtp<VECTOR_1_TYPE>& vector_1  // vector_1
  )
  {
    assert(not is_same(vector_0.impl(), vector_1.impl()));

    return assign(Expr_Selector<>(), vector_0.impl(), vector_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
       Vector_Crtp<VECTOR_0_TYPE>& vector_0,       // vector_0
       const Vector_Crtp<VECTOR_1_TYPE>& vector_1  // vector_1
  )
  {
    // v0 is unused, but the advantage is that transform checks for
    // possible static size in both v0 & v1
    transform(
        [](const auto v0_i, const auto v1_i) {
          (void)v0_i;
          return v1_i;
        },
        vector_0.impl(), vector_1.impl());

    return Expr_Selector_Enum::Generic;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
#if (HAS_BLAS)
  template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
       Dense_Vector_Crtp<VECTOR_0_TYPE>& vector_0,       // vector_0
       const Dense_Vector_Crtp<VECTOR_1_TYPE>& vector_1  // vector_1
       )
      -> std::enable_if_t<
          Always_True_v<decltype(Blas::copy(vector_0.size(), vector_1.data(), vector_1.increment(),
                                            vector_0.data(), vector_0.increment()))>,
          Expr_Selector_Enum>
  {
    assert(are_compatible_p(vector_0, vector_1));

    Blas::copy(vector_0.size(), vector_1.data(), vector_1.increment(), vector_0.data(),
               vector_0.increment());

    return selected;
  }
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  std::enable_if_t<Any_Has_Static_Size_v<VECTOR_0_TYPE, VECTOR_1_TYPE>,
                   Expr_Selector<Expr_Selector_Enum::Static>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
       Vector_Crtp<VECTOR_0_TYPE>& vector_0,       // vector_0
       const Vector_Crtp<VECTOR_1_TYPE>& vector_1  // vector_1
  )
  {
    // skip blas when V0 or v1 has a static size
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), vector_0.impl(), vector_1.impl());

    return selected;
  }
}
