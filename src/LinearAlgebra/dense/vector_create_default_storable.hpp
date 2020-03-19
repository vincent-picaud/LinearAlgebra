//
// Create default storable vector
//
// Usage example: temporary creation
//
#pragma once

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/meta/type.hpp"

namespace LinearAlgebra
{
  template <typename T, typename IMPL>
  auto
  create_default_storable(const Type<T>, const Default_Vector_Crtp<IMPL>& vector)
  {
    using vector_type =
        Default_Vector<T, typename IMPL::size_type, std::integral_constant<std::size_t, 1>>;

    return vector_type{vector.size()};
  }

  template <typename IMPL>
  auto
  create_default_storable(const Default_Vector_Crtp<IMPL>& vector)
  {
    return create_default_storable(type_v<typename IMPL::element_type>, vector);
  }
}
