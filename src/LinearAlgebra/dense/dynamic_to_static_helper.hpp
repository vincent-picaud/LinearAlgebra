#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

namespace LinearAlgebra
{
  namespace Detail
  {
    // An helper that allows contructions of a static size object from a dynamic size
    template <typename SIZE>
    struct Dynamic_To_Static_Helper
    {
      static_assert(std::is_same_v<SIZE, std::size_t>);

      std::size_t _size;
      constexpr Dynamic_To_Static_Helper(const std::size_t size) noexcept : _size(size) {}
      constexpr operator std::size_t() const noexcept { return _size; }
    };

    template <std::size_t I>
    struct Dynamic_To_Static_Helper<std::integral_constant<std::size_t, I>>
    {
      constexpr Dynamic_To_Static_Helper(const std::integral_constant<std::size_t, I>) noexcept {};
      constexpr Dynamic_To_Static_Helper(const std::size_t size) noexcept { assert(size == I); }
      constexpr operator std::integral_constant<std::size_t, I>() const noexcept { return {}; }
    };

  }  // namespace Detail

}  // namespace LinearAlgebra
