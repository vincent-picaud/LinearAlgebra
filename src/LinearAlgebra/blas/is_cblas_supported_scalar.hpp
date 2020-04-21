// TODO: to put into the Blas namespace
//
#pragma once

#if !(HAS_BLAS)
#error
#endif

#include <ccomplex>
#include <type_traits>

namespace LinearAlgebra::Blas
{
  // Split Real & Complex cases
  //================================================================

  // Real
  //
  template <typename T>
  struct Is_CBlas_Supported_Real_Scalar
      : std::integral_constant<bool, std::is_same_v<float, T> or std::is_same_v<double, T>>
  {
  };

  template <typename T>
  constexpr auto Is_CBlas_Supported_Real_Scalar_v = Is_CBlas_Supported_Real_Scalar<T>::value;

  // Complex
  //
  template <typename T>
  struct Is_CBlas_Supported_Complex_Scalar
      : std::integral_constant<bool, std::is_same_v<std::complex<float>, T> or
                                         std::is_same_v<std::complex<double>, T>>
  {
  };

  template <typename T>
  constexpr auto Is_CBlas_Supported_Complex_Scalar_v = Is_CBlas_Supported_Complex_Scalar<T>::value;

  // Real or Complex
  //
  template <typename T>
  struct Is_CBlas_Supported_Scalar
      : std::integral_constant<bool, Is_CBlas_Supported_Real_Scalar_v<T> or
                                         Is_CBlas_Supported_Complex_Scalar_v<T>>
  {
  };

  template <typename T>
  constexpr auto Is_CBlas_Supported_Scalar_v = Is_CBlas_Supported_Scalar<T>::value;
}
