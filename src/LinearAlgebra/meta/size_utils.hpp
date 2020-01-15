#pragma once

#include "LinearAlgebra/meta/is_std_integral_constant.hpp"

#include <cstddef>
#include <type_traits>

namespace LinearAlgebra
{
  /////////////////////
  // Has_Static_Size //
  /////////////////////
  //
  // Used by LinearAlgebra/expr_of_the_poor/ to switch between
  // "Generic" and "Static" subroutines
  //
  // Also see:  LinearAlgebra/dense/size_utils.hpp
  //
  template <typename IMPL, typename ENABLE = void>
  struct Has_Static_Size : std::false_type
  {
  };

  template <typename IMPL>
  struct Has_Static_Size<
      IMPL,
      std::enable_if_t<Is_Std_Integral_Constant_Of_Type_v<std::size_t, typename IMPL::size_type>>>
      : std::true_type
  {
  };

  template <typename IMPL>
  inline constexpr bool Has_Static_Size_v = Has_Static_Size<IMPL>::value;

  /////////////////////////
  // Any_Has_Static_Size //
  /////////////////////////
  //
  template <typename... IMPLs>
  struct Any_Has_Static_Size : std::integral_constant<bool, (Has_Static_Size_v<IMPLs> || ...)>
  {
  };
  template <typename... IMPLs>
  inline constexpr bool Any_Has_Static_Size_v = Any_Has_Static_Size<IMPLs...>::value;

}
