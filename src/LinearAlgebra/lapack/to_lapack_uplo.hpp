// Role:
// - To_Lapack_UpLo_v: convert a Matrix_Unary_Op_Enum into a LAPACK_UPLOW compatible value
// - Support_Lapack_UpLow_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/lapack/lapack_config.hpp"
#include "LinearAlgebra/utils/crtp.hpp"
#include "LinearAlgebra/utils/is_complete.hpp"

#if !(HAS_LAPACK)
#error
#endif

#include "LinearAlgebra/lapack/lapack_enum.hpp"

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_storage_mask_enum.hpp"

namespace LinearAlgebra
{
  namespace Lapack
  {
    template <typename T, typename ENABLE = void>
    struct To_Lapack_UpLo;

    template <>
    struct To_Lapack_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Up;
    };
    template <>
    struct To_Lapack_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Up;
    };

    template <>
    struct To_Lapack_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Low;
    };

    template <>
    struct To_Lapack_UpLo<
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>>
    {
      static constexpr Lapack_UpLo_Enum value = Lapack_UpLo_Enum::Low;
    };

    //================================================================
    //
    // Now specializations using Matrix Type
    //
    template <typename T>
    struct To_Lapack_UpLo<
        T, std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
			    // NOTE: Is_Complete etc.. is mandatory
			    //       You can try to comment it and see
			    //       the result in to_lapack_uplo.cpp
			    //       file:
			    //
			    // The test:
			    // Is_Complete_v<To_Lapack_UpLo<Matrix<double>>
			    // does NOT work anymore
			    //
                            Is_Complete_v<To_Lapack_UpLo<typename T::matrix_storage_mask_type>>>>
        : To_Lapack_UpLo<typename T::matrix_storage_mask_type>
    {
    };

    //================================================================
    //
    // Syntactic sugar
    //
    template <typename T>
    constexpr auto To_Lapack_UpLo_v = To_Lapack_UpLo<T>::value;

  }
}
