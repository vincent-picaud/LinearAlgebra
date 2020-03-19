//
// CAVEAT: keep sync with matrix_transform.hpp
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

namespace LinearAlgebra
{
  //
  // M(i,j)=lambda(M(i,j))
  //
  template <typename LAMBDA, typename IMPL>
  void
  transform(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL>& matrix)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix(i, j) = lambda(matrix.as_const()(i, j));
    };
    matrix.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  //
  // M(i,j)=lambda(M(i,j),i,j)
  //
  template <typename LAMBDA, typename IMPL>
  void
  transform_indexed(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL>& matrix)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix(i, j) = lambda(matrix.as_const()(i, j), i, j);
    };
    matrix.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }
}
