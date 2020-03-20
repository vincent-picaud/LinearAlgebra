//
// Create default storable vector
//
// Usage example: temporary creation
//
#pragma once

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_are_compatible.hpp"
#include "LinearAlgebra/meta/element_type.hpp"
#include "LinearAlgebra/meta/size_utils.hpp"
#include "LinearAlgebra/meta/type.hpp"

namespace LinearAlgebra
{
  // Create default a storable vector from vector
  //
  // If IMPL_OPTIONAL is not empty, checks that all these vectors have
  // a compatible structure and try to use any static size if any.
  //
  template <typename T, typename IMPL, typename... IMPL_OPTIONAL>
  auto
  create_default_storable(const Type<T>, const Dense_Vector_Crtp<IMPL>& vector,
                          const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional)
  {
    assert(are_compatible_p(vector.impl(), vector_optional.impl()...));

    auto vector_dest_size = get_static_size_if_any(vector.size(), vector_optional.size()...);

    using vector_type =
        Default_Vector<T, decltype(vector_dest_size), std::integral_constant<std::size_t, 1>>;

    return vector_type{vector_dest_size};
  }

  // as before but uses std::common<...> result to select "element_type"
  template <typename IMPL, typename... IMPL_OPTIONAL>
  auto
  create_default_storable(const Dense_Vector_Crtp<IMPL>& vector,
                          const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional)
  {
    return create_default_storable(type_v<Common_Element_Type_t<IMPL, IMPL_OPTIONAL...>>, vector,
                                   vector_optional...);
  }
}
