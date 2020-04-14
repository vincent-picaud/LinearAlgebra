//
// Create generic view of matrix
//
// Usage example: non-templated interface
//
// TODO: to test
//
#pragma once

#include "LinearAlgebra/dense/matrix_view.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Generic views
  //////////////////////////////////////////////////////////////////
  //
  template <typename ELEMENT_TYPE>
  using Generic_Matrix_View =
      Default_Matrix_View<ELEMENT_TYPE, Matrix_Special_Structure_Enum::None,
                          Matrix_Storage_Mask_Enum::None, std::size_t, std::size_t, std::size_t>;

  template <typename ELEMENT_TYPE>
  using Generic_Matrix_Const_View =
      Default_Matrix_Const_View<ELEMENT_TYPE, Matrix_Special_Structure_Enum::None,
                                Matrix_Storage_Mask_Enum::None, std::size_t, std::size_t,
                                std::size_t>;

  // Symmetric Matrix alias
  //
  template <typename ELEMENT_TYPE>
  using Generic_Symmetric_Matrix_View =
      Default_Matrix_View<ELEMENT_TYPE, Matrix_Special_Structure_Enum::Symmetric,
                          Matrix_Storage_Mask_Enum::Lower, std::size_t, std::size_t, std::size_t>;

  template <typename ELEMENT_TYPE>
  using Generic_Symmetric_Matrix_Const_View =
      Default_Matrix_Const_View<ELEMENT_TYPE, Matrix_Special_Structure_Enum::Symmetric,
                                Matrix_Storage_Mask_Enum::Lower, std::size_t, std::size_t,
                                std::size_t>;

  //////////////////////////////////////////////////////////////////
  // Generic views creation
  //////////////////////////////////////////////////////////////////
  //
  namespace Detail
  {
    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE,
              typename LEADING_DIMENSION>
    Default_Matrix_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, std::size_t, std::size_t,
                        std::size_t>
    create_generic_view(Default_Matrix<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE, J_SIZE,
                                       LEADING_DIMENSION>& matrix)
    {
      return {matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension()};
    }

    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE,
              typename LEADING_DIMENSION>
    Default_Matrix_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, std::size_t, std::size_t,
                        std::size_t>
    create_generic_view(Default_Matrix_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE, J_SIZE,
                                            LEADING_DIMENSION>& matrix)
    {
      return {matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension()};
    }

    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE,
              typename LEADING_DIMENSION>
    // CAVEAT: add _Const_
    Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, std::size_t, std::size_t,
                              std::size_t>
    create_generic_view(Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE,
                                                  J_SIZE, LEADING_DIMENSION>& matrix)
    {
      return {matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension()};
    }
    // Const version
    //
    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE,
              typename LEADING_DIMENSION>
    Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, std::size_t, std::size_t,
                              std::size_t>
    create_generic_view(const Default_Matrix<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE, J_SIZE,
                                             LEADING_DIMENSION>& matrix)
    {
      return {matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension()};
    }

    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE,
              typename LEADING_DIMENSION>
    Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, std::size_t, std::size_t,
                              std::size_t>
    create_generic_view(const Default_Matrix_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE,
                                                  J_SIZE, LEADING_DIMENSION>& matrix)
    {
      return {matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension()};
    }

    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE,
              typename LEADING_DIMENSION>
    Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, std::size_t, std::size_t,
                              std::size_t>
    create_generic_view(const Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK,
                                                        I_SIZE, J_SIZE, LEADING_DIMENSION>& matrix)
    {
      return {matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension()};
    }
  }

  template <typename IMPL>
  auto
  create_generic_view(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return Detail::create_generic_view(matrix.impl());
  }
  template <typename IMPL>
  auto
  create_generic_view(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return Detail::create_generic_view(matrix.impl());
  }
}
