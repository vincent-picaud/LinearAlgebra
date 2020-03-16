#pragma once

#include <ccomplex>
#include <type_traits>

namespace LinearAlgebra
{
  template <typename T>
  struct Is_CBlas_Supported_Scalar
      : std::integral_constant<bool, std::is_same_v<float, T> or std::is_same_v<double, T> or
                                         std::is_same_v<std::complex<float>, T> or
                                         std::is_same_v<std::complex<double>, T> >
  {
  };

  template <typename T>
  constexpr auto Is_CBlas_Supported_Scalar_v = Is_CBlas_Supported_Scalar<T>::value;
}
