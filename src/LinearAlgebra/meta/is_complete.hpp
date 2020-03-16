//
// From:
// - https://stackoverflow.com/a/37193089/2001017
//
#pragma once

#include <type_traits>

namespace LinearAlgebra
{
  template <class T, class = void>
  struct Is_Complete : std::false_type
  {
  };

  template <class T>
  struct Is_Complete<T, decltype(void(sizeof(T)))> : std::true_type
  {
  };

  template <class T>
  constexpr auto Is_Complete_v = Is_Complete<T>::value;
}
