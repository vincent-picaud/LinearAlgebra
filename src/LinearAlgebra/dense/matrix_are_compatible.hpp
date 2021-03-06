//
// Check that matrixs are compatible (same structure)
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"

namespace LinearAlgebra
{
  template <typename IMPL, typename... IMPL_OPTIONAL>
  constexpr bool
  are_compatible_p(const Dense_Matrix_Crtp<IMPL>& matrix,
                   const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional) noexcept
  {
    return (are_compatible_p(matrix.storage_scheme(), matrix_optional.storage_scheme()) and ...);
  }
}
