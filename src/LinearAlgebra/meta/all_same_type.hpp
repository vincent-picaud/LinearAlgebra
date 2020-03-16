// Role: check if all types of a type list are equal
//
#pragma once

#include <type_traits>

namespace LinearAlgebra
{
  namespace Detail
  {
    template <typename REF_TYPE, typename... TYPE_TO_TEST>
    struct All_Same_Type_Helper
        : std::integral_constant<bool, (std::is_same_v<REF_TYPE, TYPE_TO_TEST> && ... && true)>
    {
    };
  }

  template <typename... TYPE_TO_TEST>
  struct All_Same_Type : Detail::All_Same_Type_Helper<TYPE_TO_TEST...>
  {
  };

  template <>
  struct All_Same_Type<> : std::true_type
  {
  };

  template <typename FIRST_TYPE>
  struct All_Same_Type<FIRST_TYPE> : std::true_type
  {
  };

  template <typename... TYPE_TO_TEST>
  constexpr auto All_Same_Type_v = All_Same_Type<TYPE_TO_TEST...>::value;
}
