// Define: M = α M
//
#pragma once

#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/always.hpp"

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

// specific includes
#include "LinearAlgebra/dense/matrix_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Undefined>
  assign(const Expr_Selector<Expr_Selector_Enum::Undefined>&,
         Matrix_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Matrix_Crtp<IMPL_ARG_1>& arg_1                       // arg_1
  )
  {
    static_assert(Always_False_v<IMPL_DEST>, "Undefined");
    return {};
  }

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

  template <typename IMPL_DEST, typename IMPL_ARG_1>
  auto
  assign(Matrix_Crtp<IMPL_DEST>& dest,                              // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Matrix_Crtp<IMPL_ARG_1>& arg_1                       // arg_1
  )
  {
    return assign(Expr_Selector<>(), dest.impl(), alpha, arg_1.impl());
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
  template <typename IMPL_DEST, typename IMPL_ARG_1>
  std::integral_constant<Expr_Selector_Enum, Expr_Selector_Enum::Generic>
  assign(const Expr_Selector<Expr_Selector_Enum::Generic>&,
         Dense_Matrix_Crtp<IMPL_DEST>& dest,                        // dest
         const Common_Element_Type_t<IMPL_DEST, IMPL_ARG_1> alpha,  // alpha
         const Dense_Matrix_Crtp<IMPL_ARG_1>& arg_1                 // arg_1
  )
  {
    // Basic implementation for test
    fill_indexed(
        [alpha, &arg_1](const std::size_t i, const std::size_t j) { return alpha * arg_1(i, j); },
        dest);

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
