//
// Create default storable matrix
//
// Usage example: temporary creation
//
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/meta/type.hpp"

namespace LinearAlgebra
{
  template <typename T, typename IMPL>
  auto
  create_default_storable(const Type<T>, const Default_Matrix_Crtp<IMPL>& matrix)
  {
    // Like we use column major storage, ld is directly related to I_size
    using leading_dimension_type = typename IMPL::I_size_type;
    using matrix_type =
        Default_Matrix<T, IMPL::matrix_special_structure_type::value,
                       IMPL::matrix_storage_mask_type::value, typename IMPL::I_size_type,
                       typename IMPL::J_size_type, leading_dimension_type>;
    return matrix_type{matrix.I_size(), matrix.J_size()};
  }

  template <typename IMPL>
  auto
  create_default_storable_matrix(const Default_Matrix_Crtp<IMPL>& matrix)
  {
    return create_default_storable(type_v<typename IMPL::element_type>, matrix);
  }
}
