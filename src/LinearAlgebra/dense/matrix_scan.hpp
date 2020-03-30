//
// CAVEAT: keep sync with matrix_scan.hpp
//
#pragma once

#include "LinearAlgebra/dense/matrix_are_compatible.hpp"
#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

namespace LinearAlgebra
{
  //
  // lambda(M(i,j),Mopt(i,j)...) everything is const
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  void
  scan(const LAMBDA& lambda, const Dense_Matrix_Crtp<IMPL>& matrix,
       const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    assert(are_compatible_p(matrix, matrix_optional...));

    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      lambda(matrix(i, j), matrix_optional(i, j)...);
    };
    // For efficiency, try to catch a static size if any
    auto matrix_dest_I_size = get_static_size_if_any(matrix.I_size(), matrix_optional.I_size()...);
    auto matrix_dest_J_size = get_static_size_if_any(matrix.J_size(), matrix_optional.J_size()...);

    Detail::loop_over_indices(loop_over_indices_lambda,
                              typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
                              matrix_dest_I_size, matrix_dest_J_size);
  }

  //
  // lambda(i,j,M(i,j),Mopt(i,j)...) everything is const
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  void
  scan_indexed(const LAMBDA& lambda, const Dense_Matrix_Crtp<IMPL>& matrix,
               const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      lambda(i, j, matrix(i, j), matrix_optional(i, j)...);
    };
    // For efficiency, try to catch a static size if any
    auto matrix_dest_I_size = get_static_size_if_any(matrix.I_size(), matrix_optional.I_size()...);
    auto matrix_dest_J_size = get_static_size_if_any(matrix.J_size(), matrix_optional.J_size()...);

    Detail::loop_over_indices(loop_over_indices_lambda,
                              typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
                              matrix_dest_I_size, matrix_dest_J_size);
  }

  //////////////////////////////////////////////////////////////////

  //
  // bool <- lambda(M(i,j),Mopt(i,j)...) everything is const
  //
  // Stop as soon as the lambda return false
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  bool
  scan_while(const LAMBDA& lambda, const Dense_Matrix_Crtp<IMPL>& matrix,
             const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    assert(are_compatible_p(matrix, matrix_optional...));

    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      return lambda(matrix(i, j), matrix_optional(i, j)...);
    };
    // For efficiency, try to catch a static size if any
    auto matrix_dest_I_size = get_static_size_if_any(matrix.I_size(), matrix_optional.I_size()...);
    auto matrix_dest_J_size = get_static_size_if_any(matrix.J_size(), matrix_optional.J_size()...);

    return Detail::loop_over_indices_while(
        loop_over_indices_lambda, typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
        matrix_dest_I_size, matrix_dest_J_size);
  }
}
