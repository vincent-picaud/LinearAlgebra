// Role: create matrix views
//
// CAVEAT: read vector_view.hpp header about convention begin,end and not begin,size
//         also use this vector_view.hpp as model for internal consistency
//
// View types:
//
// * Create view from an already existing default matrix M:
//
//    - create_view_submatrix(M,I_begin,I_end,J_begin,J_end)
//
//    - create_view_matrix_type(M,structure,mask) which is declined into
//
//       - create_view_matrix_type_full(M)
//
//       - create_view_matrix_type_strict_upper_triangular(M)
//
//       - create_view_matrix_type_strict_lower_triangular(M)
//
//       - create_view_matrix_type_strict_upper_triangular(M)
//
//       - etc...
//
// * Create a matrix view from a raw pointer p:
//
//    - create_matrix_view(p,I_size,J_size,ld) [column major]
//
//    - create_matrix_view(p,I_size,J_size)    [column major, ld=I_size]
//
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

namespace LinearAlgebra
{
  /////////////////////////////////////////////////////////
  // Note: this part is the vector_view.hpp counter part //
  /////////////////////////////////////////////////////////
  //
  namespace Detail
  {
    // most basic routine that needs all the arguments
    //
    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE_TYPE, typename J_SIZE_TYPE,
              typename LEADING_DIMENSION_TYPE>
    auto
    create_view_matrix_helper(
        ELEMENT_TYPE* data,
        const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
        const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>, const I_SIZE_TYPE I_size,
        const J_SIZE_TYPE J_size, const LEADING_DIMENSION_TYPE leading_dimension)
    {
      return Default_Matrix_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE_TYPE, J_SIZE_TYPE,
                                 LEADING_DIMENSION_TYPE>(data, I_size, J_size, leading_dimension);
    }
    // Const version
    template <typename ELEMENT_TYPE, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename I_SIZE_TYPE, typename J_SIZE_TYPE,
              typename LEADING_DIMENSION_TYPE>
    auto
    create_view_matrix_helper(
        const ELEMENT_TYPE* data,
        const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
        const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>, const I_SIZE_TYPE I_size,
        const J_SIZE_TYPE J_size, const LEADING_DIMENSION_TYPE leading_dimension)
    {
      return Default_Matrix_Const_View<ELEMENT_TYPE, SPECIAL_STRUCTURE, MASK, I_SIZE_TYPE,
                                       J_SIZE_TYPE, LEADING_DIMENSION_TYPE>(data, I_size, J_size,
                                                                            leading_dimension);
    }

    //================================================================

    // A little bit more "abstract" routines where "matrix" argument
    // encapsulate stuff like mask & special structure information
    //
    template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
    auto
    create_view_submatrix(Dense_Matrix_Crtp<IMPL>& matrix, const I_BEGIN I_begin, const I_END I_end,
                          const J_BEGIN J_begin, const J_END J_end) noexcept
    {
      assert(check_size_begin_end_p(matrix.I_size(), I_begin, I_end));
      assert(check_size_begin_end_p(matrix.J_size(), J_begin, J_end));
      assert(IMPL::storage_scheme_type::matrix_storage_mask_type::value ==
                 Matrix_Storage_Mask_Enum::None or
             (I_begin == J_begin and I_end == J_end));

      auto I_size = compute_size_from_begin_end(I_begin, I_end);
      auto J_size = compute_size_from_begin_end(J_begin, J_end);

      return create_view_matrix_helper(
          &matrix(I_begin, J_begin), typename IMPL::matrix_special_structure_type(),
          typename IMPL::storage_scheme_type::matrix_storage_mask_type(), I_size, J_size,
          matrix.leading_dimension());
    }
    // Const view version
    template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
    auto
    create_view_submatrix(const Dense_Matrix_Crtp<IMPL>& matrix, const I_BEGIN I_begin,
                          const I_END I_end, const J_BEGIN J_begin, const J_END J_end) noexcept
    {
      assert(check_size_begin_end_p(matrix.I_size(), I_begin, I_end));
      assert(check_size_begin_end_p(matrix.J_size(), J_begin, J_end));
      assert(IMPL::storage_scheme_type::matrix_storage_mask_type::value ==
                 Matrix_Storage_Mask_Enum::None or
             (I_begin == J_begin and I_end == J_end));

      auto I_size = compute_size_from_begin_end(I_begin, I_end);
      auto J_size = compute_size_from_begin_end(J_begin, J_end);

      return create_view_matrix_helper(
          &matrix(I_begin, J_begin), typename IMPL::matrix_special_structure_type(),
          typename IMPL::storage_scheme_type::matrix_storage_mask_type(), I_size, J_size,
          matrix.leading_dimension());
    }
  }

  // CAVEAT: when matrix has a peculiar structure: triangular,
  //         symmetric... only views with I_begin=J_begin and
  //         I_end=J_end are allowed. The only case where this
  //         restriction does not hold is for
  //
  //           Matrix_Storage_Mask_Enum::None
  //

  template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
  auto
  create_view_submatrix(Dense_Matrix_Crtp<IMPL>& matrix, const I_BEGIN I_begin, const I_END I_end,
                        const J_BEGIN J_begin, const J_END J_end) noexcept

  {
    return Detail::create_view_submatrix(
        matrix, Detail::size_type_normalization(I_begin), Detail::size_type_normalization(I_end),
        Detail::size_type_normalization(J_begin), Detail::size_type_normalization(J_end));
  }
  // const version
  template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
  auto
  create_view_submatrix(const Dense_Matrix_Crtp<IMPL>& matrix, const I_BEGIN I_begin,
                        const I_END I_end, const J_BEGIN J_begin, const J_END J_end) noexcept

  {
    return Detail::create_view_submatrix(
        matrix, Detail::size_type_normalization(I_begin), Detail::size_type_normalization(I_end),
        Detail::size_type_normalization(J_begin), Detail::size_type_normalization(J_end));
  }

  ////////////////////////////////////////////////////
  // Create view from a raw pointer: user interface //
  ////////////////////////////////////////////////////
  //
  // Note: for simplicity we only provide an interface for Full
  //       matrix.  If the "user" wants a more specialized matrix
  //       (like a triangular one), he can build it by calling, by
  //       example:
  //
  //       create_view_strict_lower_triangular(matrix)
  //
  //       with the freshly created dense view.
  //
  // ----------------
  //
  // CAVEAT: here we use "create_matrix_view()" instead of
  //         "create_view()" to avoid possible ambiguities. By example
  //         there would be some problem between:
  //
  //         create_view(data,I_size,J_size) <- a matrix
  //         create_view(data, size,stride) <- a dense vector
  //
  template <typename ELEMENT_TYPE, typename I_SIZE, typename J_SIZE, typename LEADING_DIMENSION>
  auto
  create_matrix_view(ELEMENT_TYPE* data, const I_SIZE I_size, const J_SIZE J_size,
                     const LEADING_DIMENSION leading_dimension)
  {
    return Detail::create_view_matrix_helper(
        data,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>(),
        Detail::size_type_normalization(I_size), Detail::size_type_normalization(J_size),
        Detail::size_type_normalization(leading_dimension));
  }
  template <typename ELEMENT_TYPE, typename I_SIZE, typename J_SIZE>
  auto
  create_matrix_view(ELEMENT_TYPE* data, const I_SIZE I_size, const J_SIZE J_size)
  {
    return Detail::create_view_matrix_helper(
        data,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>(),
        Detail::size_type_normalization(I_size), Detail::size_type_normalization(J_size),
        Detail::size_type_normalization(I_size));
  }
  //
  // CAVEAT: not need to redifined "const" version, as
  //
  // template <typename ELEMENT_TYPE,...>
  //
  // automatically induce "const element_type*" when the pointer is constant
  //

  ////////////////////////////////////////////////////////////////////////////////////////////
  // CAVEAT: this part has no vector_view.hpp equivalent and is spectific to dense matrices //
  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Modify Matrix structure & mask
  //

  //
  // General routines using Enum (see shorter Alias below)
  //
  template <typename IMPL, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  auto
  create_view_matrix_type(
      Dense_Matrix_Crtp<IMPL>& matrix,
      const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
      const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>) noexcept
  {
    return Default_Matrix_View<typename IMPL::element_type, SPECIAL_STRUCTURE, MASK,
                               typename IMPL::I_size_type, typename IMPL::J_size_type,
                               typename IMPL::leading_dimension_type>(
        matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension());
  }
  // const version
  template <typename IMPL, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  auto
  create_view_matrix_type(
      const Dense_Matrix_Crtp<IMPL>& matrix,
      const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
      const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>) noexcept
  {
    return Default_Matrix_Const_View<typename IMPL::element_type, SPECIAL_STRUCTURE, MASK,
                                     typename IMPL::I_size_type, typename IMPL::J_size_type,
                                     typename IMPL::leading_dimension_type>(
        matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension());
  }
  //
  // Some ALIAS: mutable, followed by const version
  //

  // Full
  //
  template <typename IMPL>
  auto
  create_view_matrix_type_full(Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>());
  }
  template <typename IMPL>
  auto
  create_view_matrix_type_full(const Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>());
  }

  // Triangular strict
  //
  template <typename IMPL>
  auto
  create_view_matrix_type_strict_upper_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_view_matrix_type_strict_lower_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }
  // const version
  template <typename IMPL>
  auto
  create_view_matrix_type_strict_upper_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_view_matrix_type_strict_lower_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }
  // Triangular
  //
  template <typename IMPL>
  auto
  create_view_matrix_type_upper_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>());
  }

  template <typename IMPL>
  auto
  create_view_matrix_type_lower_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }
  // const version
  template <typename IMPL>
  auto
  create_view_matrix_type_upper_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>());
  }

  template <typename IMPL>
  auto
  create_view_matrix_type_lower_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }

  // Unit triangular
  //
  template <typename IMPL>
  auto
  create_view_matrix_type_unit_upper_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_view_matrix_type_unit_lower_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }
  // const version
  template <typename IMPL>
  auto
  create_view_matrix_type_unit_upper_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_view_matrix_type_unit_lower_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_view_matrix_type(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }

}
