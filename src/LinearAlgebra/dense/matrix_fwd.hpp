//
// Forward declarations
//
#pragma once

#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/matrix_storage_mask_enum.hpp"
#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"

#include <cstddef>
#include <type_traits>

namespace LinearAlgebra
{
  //
  // Storable
  //
  template <typename T,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  class Default_Matrix;

  //
  // Views
  //
  template <typename T,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  class Default_Matrix_View;

  template <typename T,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  class Default_Matrix_Const_View;

  //
  //================================================================
  // Alias
  //================================================================
  //

  //================

  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Matrix = Default_Matrix<T,
                                     Matrix_Special_Structure_Enum::None,
                                     Matrix_Storage_Mask_Enum::None,
                                     std::integral_constant<std::size_t, I_SIZE>,
                                     std::integral_constant<std::size_t, J_SIZE>,
                                     std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Matrix = Default_Matrix<T,
                                Matrix_Special_Structure_Enum::None,
                                Matrix_Storage_Mask_Enum::None,
                                std::size_t,
                                std::size_t,
                                std::size_t>;

  //================ Triangular_Strict
  //
  // CAVEAT: does not belong to Blas matrix type
  //

  // Lower
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Strict_Lower_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Lower_Strict,
                     std::integral_constant<std::size_t, I_SIZE>,
                     std::integral_constant<std::size_t, J_SIZE>,
                     std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Strict_Lower_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Lower_Strict,
                     std::size_t,
                     std::size_t,
                     std::size_t>;

  // Upper
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Strict_Upper_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Upper_Strict,
                     std::integral_constant<std::size_t, I_SIZE>,
                     std::integral_constant<std::size_t, J_SIZE>,
                     std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Strict_Upper_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Upper_Strict,
                     std::size_t,
                     std::size_t,
                     std::size_t>;

  //================ Triangular

  // Lower
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Lower_Triangular_Matrix = Default_Matrix<T,
                                                      Matrix_Special_Structure_Enum::Triangular,
                                                      Matrix_Storage_Mask_Enum::Lower,
                                                      std::integral_constant<std::size_t, I_SIZE>,
                                                      std::integral_constant<std::size_t, J_SIZE>,
                                                      std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Lower_Triangular_Matrix = Default_Matrix<T,
                                                 Matrix_Special_Structure_Enum::Triangular,
                                                 Matrix_Storage_Mask_Enum::Lower,
                                                 std::size_t,
                                                 std::size_t,
                                                 std::size_t>;

  // Upper
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Upper_Triangular_Matrix = Default_Matrix<T,
                                                      Matrix_Special_Structure_Enum::Triangular,
                                                      Matrix_Storage_Mask_Enum::Upper,
                                                      std::integral_constant<std::size_t, I_SIZE>,
                                                      std::integral_constant<std::size_t, J_SIZE>,
                                                      std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Upper_Triangular_Matrix = Default_Matrix<T,
                                                 Matrix_Special_Structure_Enum::Triangular,
                                                 Matrix_Storage_Mask_Enum::Upper,
                                                 std::size_t,
                                                 std::size_t,
                                                 std::size_t>;

  //================ Unit_Triangular

  // Lower
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Unit_Lower_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Lower_Strict,
                     std::integral_constant<std::size_t, I_SIZE>,
                     std::integral_constant<std::size_t, J_SIZE>,
                     std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Unit_Lower_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Lower_Strict,
                     std::size_t,
                     std::size_t,
                     std::size_t>;

  // Upper
  template <typename T, std::size_t I_SIZE, std::size_t J_SIZE>
  using Tiny_Unit_Upper_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Upper_Strict,
                     std::integral_constant<std::size_t, I_SIZE>,
                     std::integral_constant<std::size_t, J_SIZE>,
                     std::integral_constant<std::size_t, I_SIZE>>;

  template <typename T>
  using Unit_Upper_Triangular_Matrix =
      Default_Matrix<T,
                     Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Upper_Strict,
                     std::size_t,
                     std::size_t,
                     std::size_t>;

  //================ Symmetric (are square)

  template <typename T, std::size_t SIZE>
  using Tiny_Symmetric_Matrix = Default_Matrix<T,
                                               Matrix_Special_Structure_Enum::Symmetric,
                                               Matrix_Storage_Mask_Enum::Lower,
                                               std::integral_constant<std::size_t, SIZE>,
                                               std::integral_constant<std::size_t, SIZE>,
                                               std::integral_constant<std::size_t, SIZE>>;

  template <typename T>
  using Symmetric_Matrix = Default_Matrix<T,
                                          Matrix_Special_Structure_Enum::Symmetric,
                                          Matrix_Storage_Mask_Enum::Lower,
                                          std::size_t,
                                          std::size_t,
                                          std::size_t>;

  //================ Hermitian (are square)

  template <typename T, std::size_t SIZE>
  using Tiny_Hermitian_Matrix = Default_Matrix<T,
                                               Matrix_Special_Structure_Enum::Hermitian,
                                               Matrix_Storage_Mask_Enum::Lower,
                                               std::integral_constant<std::size_t, SIZE>,
                                               std::integral_constant<std::size_t, SIZE>,
                                               std::integral_constant<std::size_t, SIZE>>;

  template <typename T>
  using Hermitian_Matrix = Default_Matrix<T,
                                          Matrix_Special_Structure_Enum::Hermitian,
                                          Matrix_Storage_Mask_Enum::Lower,
                                          std::size_t,
                                          std::size_t,
                                          std::size_t>;

  //////////////////////////////////////////////////////////////////
  // Generic View  + Alias
  //////////////////////////////////////////////////////////////////
  //

  template <typename ELEMENT_TYPE,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  using Generic_Matrix_View = Default_Matrix_View<ELEMENT_TYPE,
                                                  SPECIAL_STRUCTURE,
                                                  MASK,
                                                  std::size_t,
                                                  std::size_t,
                                                  std::size_t>;

  template <typename ELEMENT_TYPE,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  using Generic_Matrix_Const_View = Default_Matrix_Const_View<ELEMENT_TYPE,
                                                              SPECIAL_STRUCTURE,
                                                              MASK,
                                                              std::size_t,
                                                              std::size_t,
                                                              std::size_t>;

  //----------------------------------------------------------------

  template <typename ELEMENT_TYPE>
  using Generic_Full_Matrix_View = Default_Matrix_View<ELEMENT_TYPE,
                                                       Matrix_Special_Structure_Enum::None,
                                                       Matrix_Storage_Mask_Enum::None,
                                                       std::size_t,
                                                       std::size_t,
                                                       std::size_t>;

  template <typename ELEMENT_TYPE>
  using Generic_Full_Matrix_Const_View =
      Default_Matrix_Const_View<ELEMENT_TYPE,
                                Matrix_Special_Structure_Enum::None,
                                Matrix_Storage_Mask_Enum::None,
                                std::size_t,
                                std::size_t,
                                std::size_t>;

  //----------------------------------------------------------------

  template <typename ELEMENT_TYPE>
  using Generic_Symmetric_Matrix_View =
      Default_Matrix_View<ELEMENT_TYPE,
                          Matrix_Special_Structure_Enum::Symmetric,
                          Matrix_Storage_Mask_Enum::Lower,
                          std::size_t,
                          std::size_t,
                          std::size_t>;

  template <typename ELEMENT_TYPE>
  using Generic_Symmetric_Matrix_Const_View =
      Default_Matrix_Const_View<ELEMENT_TYPE,
                                Matrix_Special_Structure_Enum::Symmetric,
                                Matrix_Storage_Mask_Enum::Lower,
                                std::size_t,
                                std::size_t,
                                std::size_t>;
}
