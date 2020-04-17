//
// Forward declarations
//
#pragma once

namespace LinearAlgebra
{
  //
  // Storable
  //
  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector;

  //
  // Views
  //
  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector_View;

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector_Const_View;

  //
  //================================================================
  // Alias
  //================================================================
  //

  template <typename T, size_t SIZE>
  using Tiny_Vector = Default_Vector<T, std::integral_constant<std::size_t, SIZE>,
                                     std::integral_constant<std::size_t, 1>>;

  template <typename T>
  using Vector = Default_Vector<T, size_t, std::integral_constant<std::size_t, 1>>;

  //
  //================================================================
  // Generic View Alias
  //================================================================
  //
  template <typename T>
  using Generic_Vector_View = Default_Vector_View<T, std::size_t, std::size_t>;

  template <typename T>
  using Generic_Vector_Const_View = Default_Vector_Const_View<T, std::size_t, std::size_t>;

}
