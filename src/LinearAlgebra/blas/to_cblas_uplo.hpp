// Role:
// - To_CBlas_UpLo_v: convert a Matrix_Unary_Op_Enum into a CBLAS_UPLOW compatible value
// - Support_CBlas_UpLow_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if !(HAS_BLAS)
#error
#endif

#include "LinearAlgebra/dense/matrix_storage_mask_enum.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    template <Matrix_Storage_Mask_Enum OP_M>
    struct To_CBlas_UpLo;

    template <>
    struct To_CBlas_UpLo<Matrix_Storage_Mask_Enum::Upper>
    {
      static constexpr CBLAS_UPLO value = CblasUpper;
    };
    template <>
    struct To_CBlas_UpLo<Matrix_Storage_Mask_Enum::Upper_Strict>
    {
      static constexpr CBLAS_UPLO value = CblasUpper;
    };

    template <>
    struct To_CBlas_UpLo<Matrix_Storage_Mask_Enum::Lower>
    {
      static constexpr CBLAS_UPLO value = CblasLower;
    };
    template <>
    struct To_CBlas_UpLo<Matrix_Storage_Mask_Enum::Lower_Strict>
    {
      static constexpr CBLAS_UPLO value = CblasLower;
    };

    template <Matrix_Storage_Mask_Enum OP_M>
    constexpr auto To_CBlas_UpLo_v = To_CBlas_UpLo<OP_M>::value;

  }
}
