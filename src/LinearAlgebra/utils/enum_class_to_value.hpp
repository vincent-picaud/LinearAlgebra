// ref: https://stackoverflow.com/a/14589519/2001017

#pragma once

#include <type_traits>  //for std::underlying_type

namespace LinearAlgebra
{
  template <typename E>
  constexpr auto
  enum_class_to_value(E e) -> typename std::underlying_type<E>::type
  {
    return static_cast<typename std::underlying_type<E>::type>(e);
  }
}
