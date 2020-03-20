#pragma once

#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

#include <cstddef>
#include <type_traits>

namespace LinearAlgebra
{
  /////////////////////
  // Has_Static_Size //
  /////////////////////
  //
  // Used by LinearAlgebra/expr/ to switch between
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

  //////////////////////////////////////////////////////////////////

  //
  // From a list of size / integral_constant<size> return the first
  // static size if any, otherwise returns the last dynamic size
  //
  // CAVEAT: declaration *order* of these two functions is important!
  //
  template <size_t N, typename... STATIC_DYNAMIC_SIZE>
  constexpr auto
  get_static_size_if_any(const std::integral_constant<size_t, N>,
                         const STATIC_DYNAMIC_SIZE... other_size) noexcept
  {
    return std::integral_constant<size_t, N>{};
  }

  template <typename... STATIC_DYNAMIC_SIZE>
  constexpr auto
  get_static_size_if_any(const size_t n, const STATIC_DYNAMIC_SIZE... other_size) noexcept
  {
    if constexpr (sizeof...(STATIC_DYNAMIC_SIZE) == 0)
    {
      return n;
    }
    else
    {
      return get_static_size_if_any(other_size...);
    }
  }

  //
  // Check that all sizes are equal
  //
  template <typename STATIC_DYNAMIC_SIZE, typename... STATIC_DYNAMIC_SIZE_TAIL>
  constexpr auto
  all_sizes_are_equal_p(const STATIC_DYNAMIC_SIZE size,
                        const STATIC_DYNAMIC_SIZE_TAIL... size_tail) noexcept
      -> std::enable_if_t<
          Is_Std_Integral_Constant_Size_Or_Std_Size_v<STATIC_DYNAMIC_SIZE> and
              (Is_Std_Integral_Constant_Size_Or_Std_Size_v<STATIC_DYNAMIC_SIZE_TAIL> and ...),
          bool>
  {
    return ((size == size_tail) and ...);
  }
}
