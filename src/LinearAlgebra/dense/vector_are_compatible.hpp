//
// Check that vectors are compatible (same structure)
//

#include "LinearAlgebra/dense/vector_storage_scheme.hpp"

namespace LinearAlgebra
{
  // CAVEAT: this relation is assymetric.
  //
  // For instance if the first vector is sparse and the other dense (but with the same size), then
  // we can safely loop over sparse vector indices to access other vectors components.
  // The reverse is *false*
  //
  template <typename IMPL, typename... IMPL_OPTIONAL>
  constexpr bool
  are_compatible_from_to_p(const Dense_Vector_Crtp<IMPL>& vector,
                           const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional) noexcept
  {
    return (are_compatible(vector.impl(), vector_optional.impl()) and ...);
  }
}