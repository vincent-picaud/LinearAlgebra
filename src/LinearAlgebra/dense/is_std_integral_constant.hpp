#pragma once

#include <type_traits>

namespace KissDStream
{
  template <typename T>
  struct is_std_integral_constant : std::false_type
  {
  };

  template <typename T, T t>
  struct is_std_integral_constant<std::integral_constant<T, t>> : std::true_type
  {
  };

  template <typename T>
  constexpr auto is_std_integral_constant_v = is_std_integral_constant<T>::value;

  //----------------------------------------------------------------

  // we use these too
  template <typename TYPE, typename T>
  struct is_std_integral_constant_of_type : std::false_type
  {
  };

  template <typename TYPE, TYPE t>
  struct is_std_integral_constant_of_type<TYPE, std::integral_constant<TYPE, t>> : std::true_type
  {
  };

  template <typename TYPE, typename T>
  constexpr auto is_std_integral_constant_of_type_v =
      is_std_integral_constant_of_type<TYPE, T>::value;

  //----------------------------------------------------------------

  template <typename T>
  constexpr auto is_std_integral_constant_size_or_std_size_v =
      (is_std_integral_constant_of_type_v<std::size_t, T> or std::is_same_v<std::size_t, T>);

}
