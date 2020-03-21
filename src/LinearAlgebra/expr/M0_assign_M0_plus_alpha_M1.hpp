//
// Compute: M0 = M0 + α M1 (Blas axpy)
//

#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename MATRIX_0_IMPL, typename MATRIX_1_IMPL>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Matrix_Crtp<MATRIX_0_IMPL>& matrix_0,                 // matrix_0
       _assign_t_,                                           // =
       _matrix_0_t_,                                         // matrix_0
       _plus_t_,                                             // +
       const typename MATRIX_0_IMPL::element_type alpha,     // alpha
       const Matrix_Crtp<MATRIX_1_IMPL>& matrix_1            // matrix_1
  )
  {
    static_assert(Always_False_v<MATRIX_0_IMPL>, "Undefined implementation");
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename MATRIX_0_IMPL, typename MATRIX_1_IMPL>
  Expr_Selector_Enum
  expr(Matrix_Crtp<MATRIX_0_IMPL>& matrix_0,              // matrix_0
       _assign_t_,                                        // =
       _matrix_0_t_,                                      // matrix_0
       _plus_t_,                                          // +
       const typename MATRIX_0_IMPL::element_type alpha,  // alpha
       const Matrix_Crtp<MATRIX_1_IMPL>& matrix_1         // matrix_1
  )
  {
    return expr(Expr_Selector<>(), matrix_0.impl(), _assign_, _matrix_0_, _plus_, alpha,
                matrix_1.impl());
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
  template <typename M_0, typename M_1>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Matrix_Crtp<M_0>& m_0,                        // matrix_0
       _assign_t_,                                         // =
       _matrix_0_t_,                                       // matrix_0
       _plus_t_,                                           // +
       const typename M_1::element_type alpha,             // alpha
       const Dense_Matrix_Crtp<M_1>& m_1                   // matrix_1
  )
  {
    assert(are_compatible_p(m_0.storage_scheme(), m_1.storage_scheme()));

    if (alpha == 0)
    {
      return Expr_Selector_Enum::Generic;  // nothing to do
    }

    if ((void*)&m_0 == (void*)&m_1)
    {
      return expr(m_0, _assign_, 1 + alpha, _matrix_0_);
    }

    if (alpha == 1)
    {
      transform([](const auto mat_0_ij, const auto mat_1_ij) { return mat_0_ij + mat_1_ij; }, m_0, m_1);
    }
    else if (alpha == -1)
    {
      transform([](const auto mat_0_ij, const auto mat_1_ij) { return mat_0_ij - mat_1_ij; }, m_0, m_1);
    }
    else
    {
      transform(
          [alpha](const auto mat_0_ij, const auto mat_1_ij) { return mat_0_ij + alpha * mat_1_ij; },
          m_0, m_1);
    }
    return Expr_Selector_Enum::Generic;
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
