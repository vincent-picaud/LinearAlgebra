//
// Check that matrixs are compatible (same structure)
//

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"

namespace LinearAlgebra
{
  // CAVEAT: this relation is assymetric.
  //
  // For instance if the first matrix is sparse and the other dense (but with the same size), then
  // we can safely loop over sparse matrix indices to access other matrixs components.
  // The reverse is *false*
  //
  template <typename IMPL, typename... IMPL_OPTIONAL>
  constexpr bool
  are_compatible_from_to_p(const Dense_Matrix_Crtp<IMPL>& matrix,
                           const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional) noexcept
  {
    return (are_compatible_p(matrix.storage_scheme(), matrix_optional.storage_scheme()) and ...);
  }
}
