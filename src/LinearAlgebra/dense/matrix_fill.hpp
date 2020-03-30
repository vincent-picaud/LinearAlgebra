//
// CAVEAT: keep sync with matrix_fill.hpp
//
#pragma once

#include "LinearAlgebra/dense/matrix_are_compatible.hpp"
#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

namespace LinearAlgebra
{
  //
  // M(i,j)=lambda(Mopt(i,j)...)
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  void
  fill(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL>& matrix,
       const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    assert(are_compatible_p(matrix, matrix_optional...));

    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix(i, j) = lambda(matrix_optional(i, j)...);
    };
    // For efficiency, try to catch a static size if any
    auto matrix_dest_I_size = get_static_size_if_any(matrix.I_size(), matrix_optional.I_size()...);
    auto matrix_dest_J_size = get_static_size_if_any(matrix.J_size(), matrix_optional.J_size()...);

    Detail::loop_over_indices(loop_over_indices_lambda,
                              typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
                              matrix_dest_I_size, matrix_dest_J_size);
  }

  //
  // M(i,j)=lambda(i,j,Mopt(i,j)...)
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  void
  fill_indexed(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL>& matrix,
               const Dense_Matrix_Crtp<IMPL_OPTIONAL>&... matrix_optional)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix(i, j) = lambda(i, j, matrix_optional(i, j)...);
    };
    // For efficiency, try to catch a static size if any
    auto matrix_dest_I_size = get_static_size_if_any(matrix.I_size(), matrix_optional.I_size()...);
    auto matrix_dest_J_size = get_static_size_if_any(matrix.J_size(), matrix_optional.J_size()...);

    Detail::loop_over_indices(loop_over_indices_lambda,
                              typename IMPL::storage_scheme_type::matrix_storage_mask_type(),
                              matrix_dest_I_size, matrix_dest_J_size);
  }
}
