#pragma once

#include <type_traits>

namespace LinearAlgebra
{
  template <typename T>
  struct Is_Std_Integral_Constant : std::false_type
  {
  };

  template <typename T, T t>
  struct Is_Std_Integral_Constant<std::integral_constant<T, t>> : std::true_type
  {
  };

  template <typename T>
  constexpr auto Is_Std_Integral_Constant_v = Is_Std_Integral_Constant<T>::value;

  //----------------------------------------------------------------

  // we use these too
  template <typename TYPE, typename T>
  struct Is_Std_Integral_Constant_Of_Type : std::false_type
  {
  };

  template <typename TYPE, TYPE t>
  struct Is_Std_Integral_Constant_Of_Type<TYPE, std::integral_constant<TYPE, t>> : std::true_type
  {
  };

  template <typename TYPE, typename T>
  constexpr auto Is_Std_Integral_Constant_Of_Type_v =
      Is_Std_Integral_Constant_Of_Type<TYPE, T>::value;

  //----------------------------------------------------------------

  template <typename T>
  constexpr auto Is_Std_Integral_Constant_Size_Or_Std_Size_v =
      (Is_Std_Integral_Constant_Of_Type_v<std::size_t, T> or std::is_same_v<std::size_t, T>);

}
