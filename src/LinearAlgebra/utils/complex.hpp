//
// Needs to extend complex with function like Z == 0
//
// Usage example:
//
//    if (scalar == 0)
//    {
//      ...
//    }
//
#pragma once

#include "LinearAlgebra/utils/type_identity.hpp"

#include <ccomplex>
#include <type_traits>

namespace LinearAlgebra
{
  // Is_Complex
  //////////////////////////////////////////////////////////////////
  //
  template <typename T>
  struct Is_Complex : std::false_type
  {
  };
  template <typename T>
  struct Is_Complex<std::complex<T>> : std::true_type
  {
  };

  template <typename T>
  constexpr auto Is_Complex_v = Is_Complex<T>::value;

  // Comparison operators
  //////////////////////////////////////////////////////////////////
  //
  template <typename T>
  bool
  operator==(const std::complex<T>& Z, const type_identity_t<T>& real) noexcept
  {
    return Z.real() == real and Z.imag() == 0;
  }

  template <typename T>
  bool
  operator!=(const std::complex<T>& Z, const type_identity_t<T>& real) noexcept
  {
    return not(Z == real);
  }

  template <typename T>
  bool
  operator==(const type_identity_t<T>& real, const std::complex<T>& Z) noexcept
  {
    return Z == real;
  }

  template <typename T>
  bool
  operator!=(const type_identity_t<T>& real, const std::complex<T>& Z) noexcept
  {
    return not(Z == real);
  }

  // Arithmetic operators
  //////////////////////////////////////////////////////////////////
  //
  template <typename T>
  auto operator*(const std::complex<T>& c, const type_identity_t<T>& s)
  {
    return c * s;
  }

  template <typename T>
  auto operator*(const type_identity_t<T>& s, const std::complex<T>& c)
  {
    return s * c;
  }

  template <typename T>
  auto
  operator/(const std::complex<T>& c, const type_identity_t<T>& s)
  {
    return c / s;
  }

  template <typename T>
  auto
  operator/(const type_identity_t<T>& s, const std::complex<T>& c)
  {
    return s / c;
  }

  template <typename T>
  auto
  operator+(const std::complex<T>& c, const type_identity_t<T>& s)
  {
    return c + s;
  }

  template <typename T>
  auto
  operator+(const type_identity_t<T>& s, const std::complex<T>& c)
  {
    return s + c;
  }

  template <typename T>
  auto
  operator-(const std::complex<T>& c, const type_identity_t<T>& s)
  {
    return c - s;
  }

  template <typename T>
  auto
  operator-(const type_identity_t<T>& s, const std::complex<T>& c)
  {
    return s - c;
  }
}
