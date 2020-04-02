// Role:
//
// - To_CBlas_Diag_v: convert a Matrix_Special_Structure_Enum into a
//        CBLAS_DIAG compatible value
//
// - Support_CBlas_Diag_v: compile-time check if this conversion is
//        possible
//
#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if !(HAS_BLAS)
#error
#endif

#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/utils/is_complete.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    template <Matrix_Special_Structure_Enum MATRIX_STRUCTURE>
    struct To_CBlas_Diag;

    template <>
    struct To_CBlas_Diag<Matrix_Special_Structure_Enum::Triangular>
    {
      static constexpr CBLAS_DIAG value = CblasNonUnit;
    };
    template <>
    struct To_CBlas_Diag<Matrix_Special_Structure_Enum::Unit_Triangular>
    {
      static constexpr CBLAS_DIAG value = CblasUnit;
    };

    template <Matrix_Special_Structure_Enum MATRIX_STRUCTURE>
    constexpr auto To_CBlas_Diag_v = To_CBlas_Diag<MATRIX_STRUCTURE>::value;

    template <Matrix_Special_Structure_Enum MATRIX_STRUCTURE>
    constexpr auto Support_CBlas_Diag_v = Is_Complete<To_CBlas_Diag<MATRIX_STRUCTURE>>::value;

  }
}
