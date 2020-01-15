#pragma once

namespace LinearAlgebra
{
  // Syntactic sugar
  template <typename T>
  struct Element_Type
  {
    using type = typename T::element_type;
  };

  template <typename T>
  using Element_Type_t = typename Element_Type<T>::type;
}
