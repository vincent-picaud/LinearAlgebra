// Role:
// - To_Lapack_UpLo_v: convert a Matrix_Unary_Op_Enum into a LAPACK_UPLOW compatible value
// - Support_Lapack_UpLow_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/lapack/lapack_config.hpp"

#if !(HAS_LAPACK)
#error
#endif

#include "LinearAlgebra/lapack/lapack_enum.hpp"

#include "LinearAlgebra/dense/matrix_storage_mask_enum.hpp"

namespace LinearAlgebra
{
  namespace Lapack
  {
    template <Matrix_Storage_Mask_Enum OP_M>
    struct To_Lapack_UpLo;

    template <>
    struct To_Lapack_UpLo<Matrix_Storage_Mask_Enum::Upper>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Up;
    };
    template <>
    struct To_Lapack_UpLo<Matrix_Storage_Mask_Enum::Upper_Strict>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Up;
    };

    template <>
    struct To_Lapack_UpLo<Matrix_Storage_Mask_Enum::Lower>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Low;
    };
    template <>
    struct To_Lapack_UpLo<Matrix_Storage_Mask_Enum::Lower_Strict>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Low;
    };

    template <Matrix_Storage_Mask_Enum OP_M>
    constexpr auto To_Lapack_UpLo_v = To_Lapack_UpLo<OP_M>::value;

  }
}
