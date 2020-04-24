// Role:
// - To_CBlas_UpLo_v: convert a Matrix_Unary_Op_Enum into a CBLAS_UPLOW compatible value
// - Support_CBlas_UpLow_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if !(HAS_BLAS)
#error
#endif

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_storage_mask_enum.hpp"
#include "LinearAlgebra/utils/crtp.hpp"
#include "LinearAlgebra/utils/is_complete.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    template <typename T, typename ENABLE = void>
    struct To_CBlas_UpLo;

    template <>
    struct To_CBlas_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>>
    {
      static constexpr CBLAS_UPLO value = CblasUpper;
    };
    template <>
    struct To_CBlas_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>>
    {
      static constexpr CBLAS_UPLO value = CblasUpper;
    };

    template <>
    struct To_CBlas_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>>
    {
      static constexpr CBLAS_UPLO value = CblasLower;
    };
    template <>
    struct To_CBlas_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>>
    {
      static constexpr CBLAS_UPLO value = CblasLower;
    };

    //================================================================
    //
    // Now specializations using Matrix Type
    //
    template <typename T>
    struct To_CBlas_UpLo<
        T,
        std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                         // NOTE: Is_Complete etc.. is mandatory
                         //       You can try to comment it and see
                         //       the result in to_blas_uplo.cpp
                         //       file:
                         //
                         // The test:
                         // Is_Complete_v<To_Blas_UpLo<Matrix<double>>
                         // does NOT work anymore
                         //
                         Is_Complete_v<To_CBlas_UpLo<typename T::matrix_storage_mask_type>>>>
        : To_CBlas_UpLo<typename T::matrix_storage_mask_type>
    {
    };

    //================================================================
    //
    // Syntactic sugar
    //
    template <typename T>
    constexpr auto To_CBlas_UpLo_v = To_CBlas_UpLo<T>::value;

  }  // namespace Blas
}  // namespace LinearAlgebra
