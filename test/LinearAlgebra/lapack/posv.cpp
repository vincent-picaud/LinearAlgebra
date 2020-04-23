#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/lapack/lapack_enum.hpp"
#include "LinearAlgebra/lapack/subroutines.hpp"
#include "LinearAlgebra/lapack/to_lapack_uplo.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/crtp.hpp"

#include <gtest/gtest.h>
#include <type_traits>

namespace LinearAlgebra
{
  // template <typename IMPL>
  // constexpr std::false_type
  // is_symmetric_matrix_p(const Crtp<IMPL>&) noexcept
  // {
  //   return {};
  // }

  // template <typename IMPL>
  // constexpr std::integral_constant<bool, (IMPL::matrix_special_structure_type::value ==
  //                                         Matrix_Special_Structure_Enum::Symmetric)>
  // is_symmetric_matrix_p(const Dense_Matrix_Crtp<IMPL>&) noexcept
  // {
  //   return {};
  // }
  // template <typename IMPL>
  // constexpr std::integral_constant<bool, (IMPL::matrix_special_structure_type::value ==
  //                                         Matrix_Special_Structure_Enum::Hermitian)>
  // is_hermitian_matrix_p(const Dense_Matrix_Crtp<IMPL>&) noexcept
  // {
  //   return {};
  // }
  // template <typename IMPL>
  // constexpr std::integral_constant<bool, (IMPL::matrix_special_structure_type::value ==
  //                                         Matrix_Special_Structure_Enum::Symmetric) or
  //                                            (IMPL::matrix_special_structure_type::value ==
  //                                             Matrix_Special_Structure_Enum::Hermitian)>
  // is_symmetric_or_hermitian_matrix_p(const Dense_Matrix_Crtp<IMPL>&) noexcept
  // {
  //   return {};
  // }
  // template <typename IMPL>
  // constexpr std::integral_constant<bool, (IMPL::matrix_special_structure_type::value ==
  //                                         Matrix_Special_Structure_Enum::None)>
  // is_full_matrix_p(const Dense_Matrix_Crtp<IMPL>&) noexcept
  // {
  //   return {};
  // }

  // template <typename T>
  // struct Is_Symmetric_Matrix : decltype(is_symmetric_matrix_p(std::declval<T>()))
  // {
  // };

  // template <typename T>
  // constexpr bool Is_Symmetric_Matrix_v = Is_Symmetric_Matrix<T>::value;

  // template <typename T>
  // struct Is_Full_Matrix : decltype(is_full_matrix_p(std::declval<T>()))
  // {
  // };

  // template <typename T>
  // constexpr bool Is_Full_Matrix_v = Is_Full_Matrix<T>::value;

  template <typename T, typename ENABLE = void>
  struct Is_Symmetric_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Symmetric_Matrix<T, std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                                                 (T::matrix_special_structure_type::value ==
                                                  Matrix_Special_Structure_Enum::Symmetric)>>
      : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Symmetric_Matrix_v = Is_Symmetric_Matrix<T>::value;

  template <typename T, typename ENABLE = void>
  struct Is_Full_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Full_Matrix<T, std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                                            (T::matrix_special_structure_type::value ==
                                             Matrix_Special_Structure_Enum::None)>> : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Full_Matrix_v = Is_Full_Matrix<T>::value;

  //================================================================

  // template <Matrix_Storage_Mask_Enum OP_M>
  //   struct To_Lapack_UpLo;

  // template<typename IMPL>
  // constexpr std::integral_constant<Lapack::Lapack_UpLo_Enum,Lapack::Lapack_UpLo_Enum::Low>
  // to_lapack_uplo(const std::integral_constant<)
  // {
  // }

  //================================================================

  template <typename MA_IMPL, typename MB_IMPL>
  auto
  posv(Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Matrix_Crtp<MB_IMPL>& B) -> std::enable_if_t<
      //
      // CAVEAT: check if we can use potentially use an incomplete
      //         type Lapack::To_Lapack_UpLo_v<MA_IMPL> instead of
      //         Lapack::Lapack_UpLo_Enum::Low in a SFINEA context.
      //
      Always_True_v<decltype(Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,  //
                                          Lapack::Lapack_UpLo_Enum::Low,            // <- here
                                          A.I_size(),                               //
                                          B.J_size(),                               //
                                          A.data(),                                 //
                                          A.leading_dimension(),                    //
                                          B.data(),                                 //
                                          B.leading_dimension()))>                  //
                                                                                    //
          and
          //
          Is_Symmetric_Matrix_v<MA_IMPL>
          //
          and
          //
          Is_Full_Matrix_v<MB_IMPL>,
      //
      lapack_int>
  {
    return Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major, Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                        A.I_size(), B.J_size(), A.data(), A.leading_dimension(), B.data(),
                        B.leading_dimension());
  }
}

using namespace LinearAlgebra;
using namespace LinearAlgebra::Lapack;

TEST(Posv, sfinae)
{
  Matrix<double> A(5, 5);
  Tiny_Symmetric_Matrix<double, 5> B;

  posv(B, A);

  EXPECT_FALSE(Is_Symmetric_Matrix_v<Vector<double>>);
}
