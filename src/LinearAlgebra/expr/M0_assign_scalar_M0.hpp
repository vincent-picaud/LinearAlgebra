//
// Compute: V0 = alpha V0
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/expr/V0_assign_scalar.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Matrix_Crtp<IMPL>& matrix_0,                          // matrix_0
       _assign_t_,                                           // =
       const typename IMPL::element_type scalar,             // scalar
       _matrix_0_t_                                          // matrix_0
  )
  {
    static_assert(Always_False_v<IMPL>, "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL>
  auto
  expr(Matrix_Crtp<IMPL>& matrix_0,               // matrix_0
       _assign_t_,                                // =
       const typename IMPL::element_type scalar,  // scalar
       _matrix_0_t_                               // matrix_0
  )
  {
    return expr(Expr_Selector<>(), matrix_0.impl(), _assign_, scalar, _matrix_0_);
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
  std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Generic>
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Matrix_Crtp<IMPL>& matrix_0,                  // matrix_0
       _assign_t_,                                         // =
       const typename IMPL::element_type scalar,           // scalar
       _matrix_0_t_                                        // matrix_0
  )
  {
    if (scalar == 0)
    {
      return expr(matrix_0, _assign_, 0);
    }

    if (scalar == 1)
    {
      return {};
    }

    if (scalar == -1)
    {
      transform([](const auto& matrix_0_i) { return -matrix_0_i; }, matrix_0);
      return {};
    }

    transform([scalar](const auto& matrix_0_i) { return matrix_0_i * scalar; }, matrix_0);

    return {};
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
