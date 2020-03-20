//
// CAVEAT: keep sync with matrix_fill.hpp
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

namespace LinearAlgebra
{
  //
  // M(i,j)=lambda()
  //
  template <typename LAMBDA, typename IMPL>
  void
  fill(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL>& matrix)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix(i, j) = lambda();
    };
    matrix.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  //
  // M(i,j)=lambda(i,j)
  //
  template <typename LAMBDA, typename IMPL>
  void
  fill_indexed(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL>& matrix)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix(i, j) = lambda(i, j);
    };
    matrix.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }
}
