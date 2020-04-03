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

namespace LinearAlgebra
{
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
}
