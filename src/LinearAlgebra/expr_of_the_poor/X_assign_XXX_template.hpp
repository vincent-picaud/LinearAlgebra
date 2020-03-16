// Role: this is only a template, not included in the meson.build file
//
// Compute:


#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/dimension.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"

#include "LinearAlgebra/meta/all_same_type.hpp"
#include "LinearAlgebra/meta/element_type.hpp"

#include "LinearAlgebra/wraps/blas/is_cblas_supported_scalar.hpp"
#include "LinearAlgebra/wraps/blas/subroutines.hpp"
#include "LinearAlgebra/wraps/blas/to_cblas_transpose.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fallback
  //////////////////////////////////////////////////////////////////
  //

  //////////////////////////////////////////////////////////////////
  // User interface
  //////////////////////////////////////////////////////////////////
  //

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
