//
// Create default storable matrix
//
// Usage example: temporary creation
//
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_are_compatible.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

#include "LinearAlgebra/utils/type.hpp"

namespace LinearAlgebra
{
  // Create default a storable matrix from matrix
  //
  // If IMPL_OPTIONAL is not empty, checks that all these matrixs have
  // a compatible structure and try to use any static size if any.
  //
  // CAVEAT: mask and shape is inherited from the *first* argument (which is IMPL)
  //
  template <typename T, typename IMPL, typename... IMPL_OPTIONAL>
  auto
  create_default_storable(const Type<T>, const Dense_Matrix_Crtp<IMPL>& matrix,
                          const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    assert(are_compatible_p(matrix.impl(), matrix_optional.impl()...));

    auto matrix_dest_I_size = get_static_size_if_any(matrix.I_size(), matrix_optional.I_size()...);
    auto matrix_dest_J_size = get_static_size_if_any(matrix.J_size(), matrix_optional.J_size()...);

    // Like we use column major storage, ld is directly related to I_size
    using leading_dimension_type = decltype(matrix_dest_I_size);
    using matrix_type =
        Default_Matrix<T, IMPL::matrix_special_structure_type::value,
                       IMPL::matrix_storage_mask_type::value, typename IMPL::I_size_type,
                       typename IMPL::J_size_type, leading_dimension_type>;
    return matrix_type{matrix_dest_I_size, matrix_dest_J_size};
  }

  template <typename IMPL, typename... IMPL_OPTIONAL>
  auto
  create_default_storable_matrix(const Dense_Matrix_Crtp<IMPL>& matrix,
                                 const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    return create_default_storable(Type_v<typename IMPL::element_type>, matrix, matrix_optional...);
  }
}
