//
// Compute: M_0 = α M_0 + β v0.v0^t (rank one update, M_0 is symmetric)
//

#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_transform.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/utils/always.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //
  template <typename M_0_IMPL, typename V_0_IMPL>
  Expr_Selector_Enum
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Matrix_Crtp<M_0_IMPL>& M_0,                           // matrix_0
       _assign_t_,                                           // =
       const typename M_0_IMPL::element_type alpha,          // alpha
       _matrix_0_t_,                                         // matrix_0
       _plus_t_,                                             // +
       const typename M_0_IMPL::element_type beta,           // beta
       Vector_Crtp<V_0_IMPL>& v_0,                           // vector_0
       _transpose_t_,                                        // transpose
       _vector_0_t_                                          // vector_0
  )
  {
    static_assert(Always_False_v<M_0_IMPL>, "Undefined implementation");
    return Expr_Selector_Enum::Undefined;
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //
  template <typename M_0_IMPL, typename V_0_IMPL>
  Expr_Selector_Enum
  expr(Matrix_Crtp<M_0_IMPL>& M_0,                   // matrix_0
       _assign_t_,                                   // =
       const typename M_0_IMPL::element_type alpha,  // alpha
       _matrix_0_t_,                                 // matrix_0
       _plus_t_,                                     // +
       const typename M_0_IMPL::element_type beta,   // beta
       Vector_Crtp<V_0_IMPL>& v_0,                   // vector_0
       _transpose_t_,                                // transpose
       _vector_0_t_                                  // vector_0
  )
  {
    assert(M_0.I_size() == M_0.J_size());
    assert(M_0.I_size() == v_0.size());

    return expr(Expr_Selector<>(), M_0.impl(), _assign_, alpha, _matrix_0_, _plus_, beta,
                v_0.impl(), _transpose_, _vector_0_);
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
  template <typename M_0_IMPL, typename V_0_IMPL>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,  // Generic implementation
       Dense_Matrix_Crtp<M_0_IMPL>& M_0,                   // matrix_0
       _assign_t_,                                         // =
       const typename M_0_IMPL::element_type alpha,        // alpha
       _matrix_0_t_,                                       // matrix_0
       _plus_t_,                                           // +
       const typename M_0_IMPL::element_type beta,         // beta
       Dense_Vector_Crtp<V_0_IMPL>& v_0,                   // vector_0
       _transpose_t_,                                      // transpose
       _vector_0_t_                                        // vector_0
       ) -> std::enable_if_t<M_0_IMPL::matrix_special_structure_type::value ==
                                 Matrix_Special_Structure_Enum::Symmetric,
                             Expr_Selector_Enum>
  {
    expr(M_0, _assign_, alpha, _matrix_0_);

    transform_indexed([beta, &v_0](const size_t i, const size_t j,
                                   const auto m_ij) { return m_ij + beta * v_0[i] * v_0[j]; },
                      M_0);
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
