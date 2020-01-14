#pragma once

namespace LinearAlgebra
{
  // Syntactic sugar
  template <typenaem T>
  struct Element_Type
  {
    using type = typename T::element_type;
  };

  template <typenaem T>
  using Element_Type_t = typename Element_Type<T>::type;
}
