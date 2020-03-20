//
// Check that vectors are compatible (same structure)
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_storage_scheme.hpp"

namespace LinearAlgebra
{
  template <typename IMPL, typename... IMPL_OPTIONAL>
  constexpr bool
  are_compatible_p(const Dense_Vector_Crtp<IMPL>& vector,
                           const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional) noexcept
  {
    return (are_compatible_p(vector.storage_scheme(), vector_optional.storage_scheme()) and ...);
  }
}
