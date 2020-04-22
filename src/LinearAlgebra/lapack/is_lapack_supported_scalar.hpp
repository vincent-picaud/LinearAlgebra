#pragma once

#include "LinearAlgebra/lapack/lapack_config.hpp"

#if !(HAS_LAPACK) 
#error
#endif

#include "LinearAlgebra/blas/is_cblas_supported_scalar.hpp"

#include <ccomplex>
#include <type_traits>

namespace LinearAlgebra::Lapack
{
  // Split Real & Complex cases
  //================================================================

  // Real
  //
  template <typename T>
  struct Is_Lapack_Supported_Real_Scalar : LinearAlgebra::Blas::Is_CBlas_Supported_Real_Scalar<T>
  {
  };

  template <typename T>
  constexpr auto Is_Lapack_Supported_Real_Scalar_v = Is_Lapack_Supported_Real_Scalar<T>::value;

  // Complex
  //
  template <typename T>
  struct Is_Lapack_Supported_Complex_Scalar : LinearAlgebra::Blas::Is_CBlas_Supported_Complex_Scalar<T>
  {
  };

  template <typename T>
  constexpr auto Is_Lapack_Supported_Complex_Scalar_v =
      Is_Lapack_Supported_Complex_Scalar<T>::value;

  // Real or Complex
  //
  template <typename T>
  struct Is_Lapack_Supported_Scalar : LinearAlgebra::Blas::Is_CBlas_Supported_Scalar<T>
  {
  };

  template <typename T>
  constexpr auto Is_Lapack_Supported_Scalar_v = Is_Lapack_Supported_Scalar<T>::value;
}
