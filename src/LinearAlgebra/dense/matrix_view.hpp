// Role: create matrix views
//
// CAVEAT: read vector_view.hpp header about convention begin,end and not begin,size
//         also use this vector_view.hpp as model for internal consistency
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
    auto
    create_view(Dense_Matrix_Crtp<IMPL>& matrix, const I_BEGIN I_begin, const I_END I_end,
                const J_BEGIN J_begin, const J_END J_end) noexcept
    {
      assert(check_size_begin_end_p(matrix.I_size(), I_begin, I_end));
      assert(check_size_begin_end_p(matrix.J_size(), J_begin, J_end));
      assert(IMPL::storage_scheme_type::matrix_storage_mask_type::value ==
                 Matrix_Storage_Mask_Enum::None or
             (I_begin == J_begin and I_end == J_end));

      auto I_size = compute_size_from_begin_end(I_begin, I_end);
      auto J_size = compute_size_from_begin_end(J_begin, J_end);

      return Default_Matrix_View<
          typename IMPL::element_type, IMPL::matrix_special_structure_type::value,
          IMPL::storage_scheme_type::matrix_storage_mask_type::value, decltype(I_size),
          decltype(J_size), typename IMPL::leading_dimension_type>(
          &matrix(I_begin, J_begin), I_size, J_size,  // CAVEAT: and not data()+I_begin
          matrix.leading_dimension());  //         which does not take into account increment
    }
    // Const view version: see vector_view.hpp for extra comments
    template <typename IMPL, typename I_BEGIN, typename I_END, typename J_BEGIN, typename J_END>
    auto
    create_view(const Dense_Matrix_Crtp<IMPL>& matrix, const I_BEGIN I_begin, const I_END I_end,
                const J_BEGIN J_begin, const J_END J_end) noexcept
    {
      assert(check_size_begin_end_p(matrix.I_size(), I_begin, I_end));
      assert(check_size_begin_end_p(matrix.J_size(), J_begin, J_end));
      assert(IMPL::storage_scheme_type::matrix_storage_mask_type::value ==
                 Matrix_Storage_Mask_Enum::None or
             (I_begin == J_begin and I_end == J_end));

      auto I_size = compute_size_from_begin_end(I_begin, I_end);
      auto J_size = compute_size_from_begin_end(J_begin, J_end);

      return Default_Matrix_Const_View<
          typename IMPL::element_type, IMPL::matrix_special_structure_type::value,
          IMPL::storage_scheme_type::matrix_storage_mask_type::value, decltype(I_size),
          decltype(J_size), typename IMPL::leading_dimension_type>(
          &matrix(I_begin, J_begin), I_size, J_size,  // CAVEAT: and not data()+I_begin
          matrix.leading_dimension());  //         which does not take into account increment
    }
  }

  // CAVEAT: when matrix has a peculiar structure: triangular,
  //         symmetric... only views with I_begin=J_begin and
  //         I_end=J_end are allowed
  //
  template <typename IMPL>
  auto
  create_view(Dense_Matrix_Crtp<IMPL>& matrix, const std::size_t I_begin, const std::size_t I_end,
              const std::size_t J_begin, const std::size_t J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  template <typename IMPL, std::size_t I_BEGIN, std::size_t I_END>
  auto
  create_view(Dense_Matrix_Crtp<IMPL>& matrix,
              const std::integral_constant<std::size_t, I_BEGIN> I_begin,
              const std::integral_constant<std::size_t, I_END> I_end, const std::size_t J_begin,
              const std::size_t J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  template <typename IMPL, std::size_t J_BEGIN, std::size_t J_END>
  auto
  create_view(Dense_Matrix_Crtp<IMPL>& matrix, const std::size_t I_begin, const std::size_t I_end,
              const std::integral_constant<std::size_t, J_BEGIN> J_begin,
              const std::integral_constant<std::size_t, J_END> J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  template <typename IMPL, std::size_t I_BEGIN, std::size_t I_END, std::size_t J_BEGIN,
            std::size_t J_END>
  auto
  create_view(Dense_Matrix_Crtp<IMPL>& matrix,
              const std::integral_constant<std::size_t, I_BEGIN> I_begin,
              const std::integral_constant<std::size_t, I_END> I_end,
              const std::integral_constant<std::size_t, J_BEGIN> J_begin,
              const std::integral_constant<std::size_t, J_END> J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  // Const view versions: only add a const to matrix argument
  //
  template <typename IMPL>
  auto
  create_view(const Dense_Matrix_Crtp<IMPL>& matrix, const std::size_t I_begin,
              const std::size_t I_end, const std::size_t J_begin, const std::size_t J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  template <typename IMPL, std::size_t I_BEGIN, std::size_t I_END>
  auto
  create_view(const Dense_Matrix_Crtp<IMPL>& matrix,
              const std::integral_constant<std::size_t, I_BEGIN> I_begin,
              const std::integral_constant<std::size_t, I_END> I_end, const std::size_t J_begin,
              const std::size_t J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  template <typename IMPL, std::size_t J_BEGIN, std::size_t J_END>
  auto
  create_view(const Dense_Matrix_Crtp<IMPL>& matrix, const std::size_t I_begin,
              const std::size_t I_end, const std::integral_constant<std::size_t, J_BEGIN> J_begin,
              const std::integral_constant<std::size_t, J_END> J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }
  template <typename IMPL, std::size_t I_BEGIN, std::size_t I_END, std::size_t J_BEGIN,
            std::size_t J_END>
  auto
  create_view(const Dense_Matrix_Crtp<IMPL>& matrix,
              const std::integral_constant<std::size_t, I_BEGIN> I_begin,
              const std::integral_constant<std::size_t, I_END> I_end,
              const std::integral_constant<std::size_t, J_BEGIN> J_begin,
              const std::integral_constant<std::size_t, J_END> J_end) noexcept

  {
    return Detail::create_view(matrix, I_begin, I_end, J_begin, J_end);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  // CAVEAT: this part has no vector_view.hpp equivalent and is spectific to dense matrices //
  ////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Modify Matrix structure & mask
  //

  template <typename IMPL, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK>
  auto
  create_view(Dense_Matrix_Crtp<IMPL>& matrix,
              const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
              const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>) noexcept
  {
    return Default_Matrix_View<typename IMPL::element_type, SPECIAL_STRUCTURE, MASK,
                               typename IMPL::I_size_type, typename IMPL::J_size_type,
                               typename IMPL::leading_dimension_type>(
        matrix.data(), matrix.I_size(), matrix.J_size(), matrix.leading_dimension());
  }
  // some alias
  template <typename IMPL>
  auto
  create_view_full(Dense_Matrix_Crtp<IMPL>& matrix) noexcept
  {
    return create_view(
        matrix,
        std::integral_constant<Matrix_Special_Structure_Enum,
                               Matrix_Special_Structure_Enum::None>(),
        std::integral_constant<Matrix_Storage_Mask_Enum, Matrix_Storage_Mask_Enum::None>());
  }
}
