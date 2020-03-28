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

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

// specific includes
#include "LinearAlgebra/dense/matrix_is_same.hpp"
#include "LinearAlgebra/dense/matrix_transform.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename MATRIX_0_TYPE, typename MATRIX_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined> selected,
         Matrix_Crtp<MATRIX_0_TYPE>& matrix_0,       // matrix_0
         const Matrix_Crtp<MATRIX_1_TYPE>& matrix_1  // matrix_1
  )
  {
    static_assert(Always_False_v<MATRIX_0_TYPE>, "Undefined implementation");
    return selected;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename MATRIX_0_TYPE, typename MATRIX_1_TYPE>
  auto
  assign(Matrix_Crtp<MATRIX_0_TYPE>& matrix_0,       // matrix_0
         const Matrix_Crtp<MATRIX_1_TYPE>& matrix_1  // matrix_1
  )
  {
    assert(not is_same(matrix_0.impl(), matrix_1.impl()));

    return assign(Expr_Selector<>(), matrix_0.impl(), matrix_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename MATRIX_0_TYPE, typename MATRIX_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Matrix_Crtp<MATRIX_0_TYPE>& matrix_0,       // matrix_0
         const Matrix_Crtp<MATRIX_1_TYPE>& matrix_1  // matrix_1
  )
  {
    // v0 is unused, but the advantage is that transform checks for
    // possible static size in both v0 & v1
    transform(
        [](const auto v0_i, const auto v1_i) {
          (void)v0_i;
          return v1_i;
        },
        matrix_0.impl(), matrix_1.impl());

    return Expr_Selector_Enum::Generic;
  }

  //================================================================
  //  Implementation: CBlas
  //================================================================
  //

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  template <typename MATRIX_0_TYPE, typename MATRIX_1_TYPE>
  std::enable_if_t<Any_Has_Static_I_Size_v<MATRIX_0_TYPE, MATRIX_1_TYPE> and
                       Any_Has_Static_J_Size_v<MATRIX_0_TYPE, MATRIX_1_TYPE>,
                   Expr_Selector<Expr_Selector_Enum::Static>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Matrix_Crtp<MATRIX_0_TYPE>& matrix_0,       // matrix_0
         const Matrix_Crtp<MATRIX_1_TYPE>& matrix_1  // matrix_1
  )
  {
    // skip blas when V0 or v1 has a static size
    assign(Expr_Selector<Expr_Selector_Enum::Generic>(), matrix_0.impl(), matrix_1.impl());

    return selected;
  }
}
