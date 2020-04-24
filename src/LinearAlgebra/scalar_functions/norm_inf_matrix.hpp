#pragma once

#include "LinearAlgebra/scalar_functions/norm_inf.hpp"

#include "LinearAlgebra/dense/matrix_scan.hpp"
#include "LinearAlgebra/expr/expr_debug.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //

  template <typename IMPL>
  auto
  norm_inf(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
           const Dense_Matrix_Crtp<IMPL>& VMT)
  {
    DEBUG_SET_SELECTED(selected);

    return Detail::norm_inf_helper(VMT);
  }

//================================================================
//  Implementation: Blas
//================================================================
//
#if (HAS_BLAS)
  // TODO
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
}
