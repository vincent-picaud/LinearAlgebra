// Role: create matrix views
//
// CAVEAT: read vector_view.hpp header about convention begin,end and not begin,size
//         also use this vector_view.hpp as model for internal consistency
//
// View types:
//
// * Create view from an already existing default matrix M:
//
//    - create_matrix_view(M, I_begin, I_end, J_begin, J_end)
//
//         -  create_matrix_view(M) a helper that simply creates a view
//
//    - create_matrix_view(M, structure, mask) which is declined into
//
//       - create_matrix_view_full(M)
//
//       - create_matrix_view_strict_upper_triangular(M)
//
//       - create_matrix_view_strict_lower_triangular(M)
//
//       - create_matrix_view_strict_upper_triangular(M)
//
//       - etc...
//
// * Create a matrix view from a raw pointer p:
//
//    - create_matrix_view(p, I_size, J_size, ld) [column major]
//
//    - create_matrix_view(p, I_size, J_size)    [column major, ld=I_size]
//
// * Create *vector* view from a matrix
//
//    - create_vector_view_matrix_row(M,i)
//
//    - create_vector_view_matrix_column(M,j)
//
//    - create_vector_view_matrix_diagonal(M,j)
//
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    /////////////////////////
    // Matrix views DETAIL //
    /////////////////////////
    //
    // Note: this part is the vector_view.hpp "Vector views DETAIL" counter part
    //

    //
    // Most versatile routine that uses all the arguments
    //
    // Note: use size_type_normalization() before calling me
    //
    template <typename ELEMENT_TYPE,
              Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK,
              typename I_SIZE,
              typename J_SIZE,
              typename LEADING_DIMENSION>
    auto
    create_matrix_view_helper(
        ELEMENT_TYPE* data,
        const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
        const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>,
        const I_SIZE I_size,
        const J_SIZE J_size,
        const LEADING_DIMENSION leading_dimension)
    {
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<I_SIZE>);
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<J_SIZE>);
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<LEADING_DIMENSION>);
      assert(leading_dimension >= I_size);

      if constexpr (std::is_const_v<ELEMENT_TYPE>)
      {
        return Default_Matrix_Const_View<std::remove_const_t<ELEMENT_TYPE>,
                                         SPECIAL_STRUCTURE,
                                         MASK,
                                         I_SIZE,
                                         J_SIZE,
                                         LEADING_DIMENSION>(
            data, I_size, J_size, leading_dimension);
      }
      else
      {
        return Default_Matrix_View<ELEMENT_TYPE,
                                   SPECIAL_STRUCTURE,
                                   MASK,
                                   I_SIZE,
                                   J_SIZE,
                                   LEADING_DIMENSION>(data, I_size, J_size, leading_dimension);
      }
    }
  }  // namespace Detail

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
  //       with the previously created dense view from the raw
  //       pointer.
  //
  // ----------------
  //
  // CAVEAT: here we use "create_matrix_view()" instead of
  //         "create_view()" to avoid possible ambiguities. By example
  //         there would be some problem between:
  //
  //         create_view(data, I_size, J_size) <- a matrix
  //         create_view(data, size, stride)   <- a dense vector
  //
  template <typename ELEMENT_TYPE, typename I_SIZE, typename J_SIZE, typename LEADING_DIMENSION>
  auto
  create_matrix_view(ELEMENT_TYPE* data,
                     const I_SIZE I_size,
                     const J_SIZE J_size,
                     const LEADING_DIMENSION leading_dimension)
  {
    return Detail::create_matrix_view_helper(
        data,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>(),
        Detail::size_type_normalization(I_size),
        Detail::size_type_normalization(J_size),
        Detail::size_type_normalization(leading_dimension));
  }
  // default leading_dimension=I_size
  template <typename ELEMENT_TYPE, typename I_SIZE, typename J_SIZE>
  auto
  create_matrix_view(ELEMENT_TYPE* data, const I_SIZE I_size, const J_SIZE J_size)
  {
    return create_matrix_view(data,
                              Detail::size_type_normalization(I_size),
                              Detail::size_type_normalization(J_size),
                              Detail::size_type_normalization(I_size));
  }

  ////////////////////////////////////////
  // User interface: submatrices views //
  ///////////////////////////////////////
  //
  // CAVEAT: when matrix has a peculiar structure: triangular,
  //         symmetric... only views with I_begin=J_begin and
  //         I_end=J_end are allowed. The only case where this
  //         restriction does not hold is for
  //
  //           Matrix_Storage_Mask_Enum::None
  //
  namespace Detail
  {
    template <typename IMPL>
    bool
    check_create_matrix_view_arguments_p(const Dense_Matrix_Crtp<IMPL>& matrix,
                                         const std::size_t I_begin,
                                         const std::size_t I_end,
                                         const std::size_t J_begin,
                                         const std::size_t J_end) noexcept
    {
      bool ok = true;
      ok &= check_size_begin_end_p(matrix.I_size(), I_begin, I_end);
      ok &= check_size_begin_end_p(matrix.J_size(), J_begin, J_end);
      ok &= IMPL::storage_scheme_type::matrix_storage_mask_type::value ==
                Matrix_Storage_Mask_Enum::None or
            (I_begin == J_begin and I_end == J_end);
      return ok;
    }
  }  // namespace Detail

  template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
  auto
  create_matrix_view(Dense_Matrix_Crtp<IMPL>& matrix,
                     const I_BEGIN I_begin,
                     const I_END I_end,
                     const J_BEGIN J_begin,
                     const J_END J_end) noexcept
  {
    assert(Detail::check_create_matrix_view_arguments_p(matrix, I_begin, I_end, J_begin, J_end));

    auto I_size = Detail::compute_size_from_begin_end(I_begin, I_end);
    auto J_size = Detail::compute_size_from_begin_end(J_begin, J_end);

    return Detail::create_matrix_view_helper(
        &matrix(I_begin, J_begin),
        typename IMPL::matrix_special_structure_type(),
        typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
        I_size,
        J_size,
        matrix.leading_dimension());
  }

  template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
  auto
  create_matrix_view(const Dense_Matrix_Crtp<IMPL>& matrix,
                     const I_BEGIN I_begin,
                     const I_END I_end,
                     const J_BEGIN J_begin,
                     const J_END J_end) noexcept
  {
    assert(Detail::check_create_matrix_view_arguments_p(matrix, I_begin, I_end, J_begin, J_end));

    auto I_size = Detail::compute_size_from_begin_end(I_begin, I_end);
    auto J_size = Detail::compute_size_from_begin_end(J_begin, J_end);

    return Detail::create_matrix_view_helper(
        &matrix(I_begin, J_begin),
        typename IMPL::matrix_special_structure_type(),
        typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
        I_size,
        J_size,
        matrix.leading_dimension());
  }

  //
  // Helper that create view (same dimension etc...)
  //
  template <typename IMPL>
  auto
  create_matrix_view(Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_matrix_view(matrix,
                              std::integral_constant<size_t, 0>(),
                              matrix.I_size(),
                              std::integral_constant<size_t, 0>(),
                              matrix.J_size());
  }
  // const
  template <typename IMPL>
  auto
  create_matrix_view(const Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_matrix_view(matrix,
                              std::integral_constant<size_t, 0>(),
                              matrix.I_size(),
                              std::integral_constant<size_t, 0>(),
                              matrix.J_size());
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  // CAVEAT: this part has no vector_view.hpp equivalent and is spectific to dense matrices //
  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Modify Matrix structure & mask
  //

  //
  // General routines using Enum (see shorter Alias below)
  //
  template <typename IMPL,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  auto
  create_matrix_view(Dense_Matrix_Crtp<IMPL>& matrix,
                     const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
                     const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>) noexcept
  {
    return Default_Matrix_View<typename IMPL::element_type,
                               SPECIAL_STRUCTURE,
                               MASK,
                               typename IMPL::I_size_type,
                               typename IMPL::J_size_type,
                               typename IMPL::leading_dimension_type>(
        matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension());
  }
  // const version
  template <typename IMPL,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  auto
  create_matrix_view(const Dense_Matrix_Crtp<IMPL>& matrix,
                     const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
                     const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>) noexcept
  {
    return Default_Matrix_Const_View<typename IMPL::element_type,
                                     SPECIAL_STRUCTURE,
                                     MASK,
                                     typename IMPL::I_size_type,
                                     typename IMPL::J_size_type,
                                     typename IMPL::leading_dimension_type>(
        matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension());
  }

  //================================================================
  // Some ALIAS: mutable, followed by const version
  //================================================================

  // Full
  //
  template <typename IMPL>
  auto
  create_matrix_view_full(Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>());
  }
  template <typename IMPL>
  auto
  create_matrix_view_full(const Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>());
  }

  // Triangular strict
  //
  template <typename IMPL>
  auto
  create_matrix_view_strict_upper_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_matrix_view_strict_lower_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }
  // const version
  template <typename IMPL>
  auto
  create_matrix_view_strict_upper_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_matrix_view_strict_lower_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular_Strict>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }
  // Triangular
  //
  template <typename IMPL>
  auto
  create_matrix_view_upper_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>());
  }

  template <typename IMPL>
  auto
  create_matrix_view_lower_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }
  // const version
  template <typename IMPL>
  auto
  create_matrix_view_upper_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper>());
  }

  template <typename IMPL>
  auto
  create_matrix_view_lower_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }

  // Unit triangular
  //
  template <typename IMPL>
  auto
  create_matrix_view_unit_upper_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_matrix_view_unit_lower_triangular(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }
  // const version
  template <typename IMPL>
  auto
  create_matrix_view_unit_upper_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Upper_Strict>());
  }

  template <typename IMPL>
  auto
  create_matrix_view_unit_lower_triangular(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Unit_Triangular>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower_Strict>());
  }

  // Symmetric Matrix
  //
  // Note: for the moment, in order to have only one Symmetric matrix
  // type, we only provide the "default" mask which is Lower
  //
  template <typename IMPL>
  auto
  create_matrix_view_symmetric(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Symmetric>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }
  // const version
  template <typename IMPL>
  auto
  create_matrix_view_symmetric(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Symmetric>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }

  // Hermitian Matrix
  //
  // Note: for the moment, in order to have only one Hermitian matrix
  // type, we only provide the "default" mask which is Lower
  //
  // CAVEAT: we do not check that diagonal is real
  //
  template <typename IMPL>
  auto
  create_matrix_view_Hermitian(Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Hermitian>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }
  // const version
  template <typename IMPL>
  auto
  create_matrix_view_Hermitian(const Dense_Matrix_Crtp<IMPL>& matrix)
  {
    return create_matrix_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::Hermitian>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::Lower>());
  }

  ///////////////////////
  // Row / Column view //
  ///////////////////////

  //
  // Note: as I_row is dynamic, everything is dynamic apart
  //       Matrix_Storage_Mask_Enum::None where row size is
  //       independent of i
  //
#define LINALG_CODE_NO_DUPLICATE(CONST)                                                      \
  template <typename IMPL>                                                                   \
  auto create_vector_view_matrix_row(CONST Dense_Matrix_Crtp<IMPL>& matrix,                  \
                                     const std::size_t I_row) noexcept                       \
  {                                                                                          \
    assert(I_row < matrix.I_size());                                                         \
    constexpr Matrix_Storage_Mask_Enum mask =                                                \
        IMPL::storage_scheme_type::matrix_storage_mask_type::value;                          \
                                                                                             \
    const auto leading_dimension = matrix.leading_dimension();                               \
                                                                                             \
    if constexpr (mask == Matrix_Storage_Mask_Enum::None)                                    \
    {                                                                                        \
      return create_vector_view(&matrix(I_row, 0), matrix.J_size(), leading_dimension);      \
    }                                                                                        \
    else                                                                                     \
    {                                                                                        \
      std::size_t memory_offset;                                                             \
      std::size_t J_size;                                                                    \
                                                                                             \
      /* Note: we use offset as it does not perform bound check */                           \
      switch (mask)                                                                          \
      {                                                                                      \
        case Matrix_Storage_Mask_Enum::Lower:                                                \
          memory_offset = matrix.storage_scheme().offset(I_row, 0);                          \
          J_size        = I_row + 1;                                                         \
          break;                                                                             \
                                                                                             \
        case Matrix_Storage_Mask_Enum::Lower_Strict:                                         \
          memory_offset = matrix.storage_scheme().offset(I_row, 0);                          \
          J_size        = I_row;                                                             \
          break;                                                                             \
                                                                                             \
        case Matrix_Storage_Mask_Enum::Upper:                                                \
          memory_offset = matrix.storage_scheme().offset(I_row, I_row);                      \
          J_size        = (matrix.J_size() > I_row) ? matrix.J_size() - I_row : 0;           \
          break;                                                                             \
                                                                                             \
        case Matrix_Storage_Mask_Enum::Upper_Strict:                                         \
          memory_offset = matrix.storage_scheme().offset(I_row, I_row + 1);                  \
          J_size        = (matrix.J_size() > I_row + 1) ? matrix.J_size() - (I_row + 1) : 0; \
                                                                                             \
          break;                                                                             \
                                                                                             \
        default:                                                                             \
          assert(0 && "Undefined type");                                                     \
      }                                                                                      \
                                                                                             \
      J_size = std::min<std::size_t>(matrix.J_size(), J_size);                               \
                                                                                             \
      return create_vector_view(matrix.data() + memory_offset, J_size, leading_dimension);   \
    }                                                                                        \
  }

  LINALG_CODE_NO_DUPLICATE()
  LINALG_CODE_NO_DUPLICATE(const)

#undef LINALG_CODE_NO_DUPLICATE

#define LINALG_CODE_NO_DUPLICATE(CONST)                                                              \
  template <typename IMPL>                                                                           \
  auto create_vector_view_matrix_column(CONST Dense_Matrix_Crtp<IMPL>& matrix,                       \
                                        const std::size_t J_column) noexcept                         \
  {                                                                                                  \
    assert(J_column < matrix.J_size());                                                              \
    constexpr Matrix_Storage_Mask_Enum mask =                                                        \
        IMPL::storage_scheme_type::matrix_storage_mask_type::value;                                  \
                                                                                                     \
    const std::integral_constant<std::size_t, 1> leading_dimension;                                  \
                                                                                                     \
    if constexpr (mask == Matrix_Storage_Mask_Enum::None)                                            \
    {                                                                                                \
      return create_vector_view(&matrix(0, J_column), matrix.I_size(), leading_dimension);           \
    }                                                                                                \
    else                                                                                             \
    {                                                                                                \
      std::size_t memory_offset;                                                                     \
      std::size_t I_size;                                                                            \
                                                                                                     \
      switch (mask)                                                                                  \
      {                                                                                              \
        case Matrix_Storage_Mask_Enum::Lower:                                                        \
          memory_offset = matrix.storage_scheme().offset(J_column, J_column);                        \
          I_size        = (matrix.I_size() > J_column) ? matrix.I_size() - J_column : 0;             \
          break;                                                                                     \
                                                                                                     \
        case Matrix_Storage_Mask_Enum::Lower_Strict:                                                 \
          memory_offset = matrix.storage_scheme().offset(J_column + 1, J_column);                    \
          I_size        = (matrix.I_size() > (J_column + 1)) ? matrix.I_size() - (J_column + 1) : 0; \
          break;                                                                                     \
                                                                                                     \
        case Matrix_Storage_Mask_Enum::Upper:                                                        \
          memory_offset = matrix.storage_scheme().offset(0, J_column);                               \
          I_size        = J_column + 1;                                                              \
          break;                                                                                     \
                                                                                                     \
        case Matrix_Storage_Mask_Enum::Upper_Strict:                                                 \
          memory_offset = matrix.storage_scheme().offset(0, J_column);                               \
          I_size        = J_column;                                                                  \
          break;                                                                                     \
                                                                                                     \
        default:                                                                                     \
          assert(0 && "Undefined type");                                                             \
      }                                                                                              \
                                                                                                     \
      I_size = std::min<std::size_t>(matrix.I_size(), I_size);                                       \
                                                                                                     \
      return create_vector_view(matrix.data() + memory_offset, I_size, leading_dimension);           \
    }                                                                                                \
  }

  LINALG_CODE_NO_DUPLICATE()
  LINALG_CODE_NO_DUPLICATE(const)

#undef LINALG_CODE_NO_DUPLICATE

  ///////////////////
  // Diagonal view //
  ///////////////////

  namespace Detail
  {
    constexpr std::size_t
    increment(const std::size_t ld) noexcept
    {
      return ld + 1;
    }
    template <std::size_t N>
    constexpr std::integral_constant<std::size_t, N + 1>
    increment(const std::integral_constant<std::size_t, N>) noexcept
    {
      return {};
    }

  }  // namespace Detail

#define LINALG_CODE_NO_DUPLICATE(CONST)                                                     \
  template <typename IMPL>                                                                  \
  auto create_vector_view_matrix_diagonal(CONST Dense_Matrix_Crtp<IMPL>& matrix) noexcept   \
  {                                                                                         \
    if constexpr (Has_Static_I_Size_v<IMPL> && Has_Static_J_Size_v<IMPL>)                   \
    {                                                                                       \
      if constexpr (IMPL::I_size_type::value <= IMPL::J_size_type::value)                   \
      {                                                                                     \
        return create_vector_view(                                                          \
            matrix.data(), matrix.I_size(), Detail::increment(matrix.leading_dimension())); \
      }                                                                                     \
      else                                                                                  \
      {                                                                                     \
        return create_vector_view(                                                          \
            matrix.data(), matrix.J_size(), Detail::increment(matrix.leading_dimension())); \
      }                                                                                     \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
      return create_vector_view(matrix.data(),                                              \
                                std::min<std::size_t>(matrix.I_size(), matrix.J_size()),    \
                                Detail::increment(matrix.leading_dimension()));             \
    }                                                                                       \
  }

  LINALG_CODE_NO_DUPLICATE()
  LINALG_CODE_NO_DUPLICATE(const)

#undef LINALG_CODE_NO_DUPLICATE

}  // namespace LinearAlgebra
