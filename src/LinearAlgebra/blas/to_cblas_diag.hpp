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

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/utils/crtp.hpp"
#include "LinearAlgebra/utils/is_complete.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    template <typename T, typename ENABLE = void>
    struct To_CBlas_Diag;

    template <>
    struct To_CBlas_Diag<std::integral_constant<Matrix_Special_Structure_Enum,
                                                Matrix_Special_Structure_Enum::Triangular>>
    {
      static constexpr CBLAS_DIAG value = CblasNonUnit;
    };
    template <>
    struct To_CBlas_Diag<std::integral_constant<Matrix_Special_Structure_Enum,
                                                Matrix_Special_Structure_Enum::Unit_Triangular>>
    {
      static constexpr CBLAS_DIAG value = CblasUnit;
    };

    //================================================================
    //
    // Now specializations using Matrix Type
    //
    template <typename T>
    struct To_CBlas_Diag<
        T,
        std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                         // NOTE: Is_Complete etc.. is mandatory
                         //       You can try to comment it and see
                         //       the result in To_CBlas_Diag.cpp
                         //       file:
                         //
                         // The test:
                         // Is_Complete_v<To_CBlas_Diag<Matrix<double>>
                         // does NOT work anymore
                         //
                         Is_Complete_v<To_CBlas_Diag<typename T::matrix_special_structure_type>>>>
        : To_CBlas_Diag<typename T::matrix_special_structure_type>
    {
    };

    //================================================================
    //
    // Syntactic sugar
    //
    template <typename T>
    constexpr auto To_CBlas_Diag_v = To_CBlas_Diag<T>::value;

    template <typename T>
    constexpr auto Support_CBlas_Diag_v =
        Is_Complete_v<To_CBlas_Diag<T>>;  // CAVEAT To_CBlas_Diag<T> and not To_CBlas_Diag_v<T> !

  }  // namespace Blas
}  // namespace LinearAlgebra
