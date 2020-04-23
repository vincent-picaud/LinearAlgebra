// A collection of compile-time predicate, mostly used in SFINAE
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  //
  // Tests using Matrix_Special_Structure_Enum
  //
  //////////////////////////////////////////////////////////////////
  //
  // Note: in the future you can add further specializations if required
  //
  //----------------------------------------------------------------

  template <typename T, typename ENABLE = void>
  struct Is_Full_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Full_Matrix<T,
                        std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                                         (T::matrix_special_structure_type::value ==
                                          Matrix_Special_Structure_Enum::None)>> : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Full_Matrix_v = Is_Full_Matrix<T>::value;

  //----------------------------------------------------------------

  template <typename T, typename ENABLE = void>
  struct Is_Symmetric_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Symmetric_Matrix<T,
                             std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                                              (T::matrix_special_structure_type::value ==
                                               Matrix_Special_Structure_Enum::Symmetric)>>
      : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Symmetric_Matrix_v = Is_Symmetric_Matrix<T>::value;

  //----------------------------------------------------------------

  template <typename T, typename ENABLE = void>
  struct Is_Hermitian_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Hermitian_Matrix<T,
                             std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                                              (T::matrix_special_structure_type::value ==
                                               Matrix_Special_Structure_Enum::Hermitian)>>
      : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Hermitian_Matrix_v = Is_Hermitian_Matrix<T>::value;

  //----------------------------------------------------------------

  template <typename T, typename ENABLE = void>
  struct Is_Triangular_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Triangular_Matrix<T,
                              std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                                               (T::matrix_special_structure_type::value ==
                                                Matrix_Special_Structure_Enum::Triangular)>>
      : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Triangular_Matrix_v = Is_Triangular_Matrix<T>::value;

  //----------------------------------------------------------------

  template <typename T, typename ENABLE = void>
  struct Is_Unit_Triangular_Matrix : std::false_type
  {
  };

  template <typename T>
  struct Is_Unit_Triangular_Matrix<
      T,
      std::enable_if_t<Is_Crtp_Interface_Of_v<Dense_Matrix_Crtp, T> and
                       (T::matrix_special_structure_type::value ==
                        Matrix_Special_Structure_Enum::Unit_Triangular)>> : std::true_type
  {
  };

  template <typename T>
  constexpr bool Is_Unit_Triangular_Matrix_v = Is_Unit_Triangular_Matrix<T>::value;

}
