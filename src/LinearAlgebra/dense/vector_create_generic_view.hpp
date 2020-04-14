//
// Create generic view of vector
//
// Usage example: non-templated interface
//
#pragma once

#include "LinearAlgebra/dense/vector_view.hpp"

namespace LinearAlgebra
{
  // Generic views
  //
  template <typename T>
  using Generic_Vector_View = Default_Vector_View<T, std::size_t, std::size_t>;

  template <typename T>
  using Generic_Vector_Const_View = Default_Vector_Const_View<T, std::size_t, std::size_t>;

  template <typename IMPL>
  auto
  create_generic_view(Dense_Vector_Crtp<IMPL>& vector)
  {
    // Note: should return either a  Generic_Vector_View or a Generic_Vector_Const_View
    return create_vector_view(vector.data(), (size_t)vector.size(), (size_t)vector.increment());
  }
  template <typename IMPL>
  auto
  create_generic_view(const Dense_Vector_Crtp<IMPL>& vector)
  {
    // Note: should return either a  Generic_Vector_View or a Generic_Vector_Const_View
    return create_vector_view(vector.data(), (size_t)vector.size(), (size_t)vector.increment());
  }

}
