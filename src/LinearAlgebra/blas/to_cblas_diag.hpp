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
#include "LinearAlgebra/utils/undefined.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    // Concerning SFINAE it is more robust to always allows _possible_ initialization than to introduce "incomplete type":
    //
    // See:
    //      https://stackoverflow.com/questions/44340209/special-rules-regarding-sfinae-for-incomplete-types
    //      https://stackoverflow.com/questions/15260685/what-exactly-is-the-immediate-context-mentioned-in-the-c11-standard-for-whic
    //
    // Concretely, here, introducing an incomplete type:
    //
    // template <typename T, typename ENABLE = void>
    // struct To_CBlas_Diag;
    //
    // causes some troubles that are fixed with a "complete" type
    // (which is always instantiatable) defined as follows:
    //
    // Another advantage is that with "complete" type you can always define:
    //
    // template <Matrix_Unary_Op_Enum OP, typename X_IMPL, typename M_IMPL>
    // auto
    // trmv(const _matrix_unary_op_t_<OP> op,
    //      const Dense_Matrix_Crtp<M_IMPL>& M,
    //      Dense_Vector_Crtp<X_IMPL>& x)
    //     -> std::enable_if_t<Always_True_v<decltype(Blas::trmv(CblasColMajor,
    //                                                           To_CBlas_UpLo_v<M_IMPL>,
    //                                                           To_CBlas_Transpose_v<OP>,
    //                                                           To_CBlas_Diag_v<M_IMPL>,   // <- here smoothly instantiate
    //                                                           M.I_size(),
    //                                                           M.data(),
    //                                                           M.leading_dimension(),
    //                                                           x.data(),
    //                                                           x.increment()))>>
    template <typename T, typename ENABLE = void>
    struct To_CBlas_Diag
    {
      static constexpr Undefined value{};
    };

    // Then the predicate to check if defined or not
    template <typename T>
    struct Support_CBlas_Diag
        : std::integral_constant<
              bool,
              not std::is_same_v<decltype(To_CBlas_Diag<T>::value), const Undefined>>
    {
    };

    //================================================================

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
    constexpr auto Support_CBlas_Diag_v = Support_CBlas_Diag<T>::value;

  }  // namespace Blas
}  // namespace LinearAlgebra
