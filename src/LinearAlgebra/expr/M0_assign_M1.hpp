//
// Matrix copy operations
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

#include "LinearAlgebra/dense/matrix_are_compatible.hpp"
#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/matrix_transform.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename M_0_TYPE, typename M_1_TYPE>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,
       Dense_Matrix_Crtp<M_0_TYPE>& matrix_0,       // matrix_0
       _assign_t_,                                  // =
       const Dense_Matrix_Crtp<M_1_TYPE>& matrix_1  // matrix_1
  )
  {
    static_assert(Always_False_v<M_0_TYPE>, "Undefined implementation");
    return Expr_Selector_Enum::Undefined;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename M_0_TYPE, typename M_1_TYPE>
  Expr_Selector_Enum
  expr(Dense_Matrix_Crtp<M_0_TYPE>& matrix_0,       // matrix_0
       _assign_t_,                                  // =
       const Dense_Matrix_Crtp<M_1_TYPE>& matrix_1  // matrix_1
  )
  {
    return expr(Expr_Selector<>(), matrix_0.impl(), _assign_, matrix_1.impl());
  }

  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename M_0_TYPE, typename M_1_TYPE>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,
       Dense_Matrix_Crtp<M_0_TYPE>& matrix_0,       // matrix_0
       _assign_t_,                                  // =
       const Dense_Matrix_Crtp<M_1_TYPE>& matrix_1  // matrix_1
  )
  {
    assert(are_compatible_p(matrix_0, matrix_1));

    // matrix_0_ij is unused, but the advantage is that transform
    // checks for possible static size in both matrix_0 & matrix_1
    transform(
        [](const auto matrix_0_ij, const auto matrix_1_ij) {
          (void)matrix_0_ij;
          return matrix_1_ij;
        },
        matrix_0, matrix_1);

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

}
