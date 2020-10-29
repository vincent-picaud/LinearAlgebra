#pragma once

#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

#include <cstddef>
#include <type_traits>

namespace LinearAlgebra
{
  /////////////////////////
  // Has_Static_Capacity //
  /////////////////////////
  //
  // Check if the memory chunk can have a static size
  //
  // Example:
  // #+BEGIN_SRC cpp :eval never
  // static_assert(not Has_Static_Capacity_v<Matrix<int>>);
  // static_assert(Has_Static_Capacity_v<Tiny_Matrix<int,2,3>>);
  // static_assert(Has_Static_Capacity_v<Tiny_Vector<int,2>>);
  // #+END_SRC
  //
  template <typename IMPL, typename ENABLE = void>
  struct Has_Static_Capacity : std::false_type
  {
  };

  template <typename IMPL>
  struct Has_Static_Capacity<IMPL,
                             std::enable_if_t<Is_Std_Integral_Constant_Of_Type_v<
                                 std::size_t,
                                 typename IMPL::storage_scheme_type::required_capacity_type>>>
      : std::true_type
  {
  };

  template <typename IMPL>
  inline constexpr bool Has_Static_Capacity_v = Has_Static_Capacity<IMPL>::value;

  /////////////////////
  // Has_Static_Size //
  /////////////////////
  //
  // Used by LinearAlgebra/expr/ to switch between
  // "Generic" and "Static" subroutines
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

  // Same as before, extension to Matrix with I_size_type, J_size_type
  //================================================================

  template <typename IMPL, typename ENABLE = void>
  struct Has_Static_I_Size : std::false_type
  {
  };

  template <typename IMPL>
  struct Has_Static_I_Size<
      IMPL,
      std::enable_if_t<Is_Std_Integral_Constant_Of_Type_v<std::size_t, typename IMPL::I_size_type>>>
      : std::true_type
  {
  };

  template <typename IMPL>
  inline constexpr bool Has_Static_I_Size_v = Has_Static_I_Size<IMPL>::value;

  /////////////////////////
  // Any_Has_Static_I_Size //
  /////////////////////////
  //
  template <typename... IMPLs>
  struct Any_Has_Static_I_Size : std::integral_constant<bool, (Has_Static_I_Size_v<IMPLs> || ...)>
  {
  };
  template <typename... IMPLs>
  inline constexpr bool Any_Has_Static_I_Size_v = Any_Has_Static_I_Size<IMPLs...>::value;

  //================

  template <typename IMPL, typename ENABLE = void>
  struct Has_Static_J_Size : std::false_type
  {
  };

  template <typename IMPL>
  struct Has_Static_J_Size<
      IMPL,
      std::enable_if_t<Is_Std_Integral_Constant_Of_Type_v<std::size_t, typename IMPL::J_size_type>>>
      : std::true_type
  {
  };

  template <typename IMPL>
  inline constexpr bool Has_Static_J_Size_v = Has_Static_J_Size<IMPL>::value;

  /////////////////////////
  // Any_Has_Static_J_Size //
  /////////////////////////
  //
  template <typename... IMPLs>
  struct Any_Has_Static_J_Size : std::integral_constant<bool, (Has_Static_J_Size_v<IMPLs> || ...)>
  {
  };
  template <typename... IMPLs>
  inline constexpr bool Any_Has_Static_J_Size_v = Any_Has_Static_J_Size<IMPLs...>::value;

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
                         const STATIC_DYNAMIC_SIZE...) noexcept
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
    (void)size;

    return ((size == size_tail) and ...);
  }
}  // namespace LinearAlgebra
