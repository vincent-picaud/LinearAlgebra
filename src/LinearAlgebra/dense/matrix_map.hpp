//
// CAVEAT: keep sync with vector_map.hpp
//
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_create_default_storable.hpp"

namespace LinearAlgebra
{
  // CAVEAT: deprecated
  template <typename LAMBDA, typename IMPL_DEST, typename IMPL_SRC>
  void
  inplace_map(const LAMBDA& lambda, Dense_Matrix_Crtp<IMPL_DEST>& matrix_dest,
              const Dense_Matrix_Crtp<IMPL_SRC>& matrix_src)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix_dest(i, j) = lambda(matrix_src.as_const()(i, j));
    };
    matrix_dest.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  template <typename LAMBDA, typename IMPL_SRC>
  auto
  map(const LAMBDA& lambda, const Dense_Matrix_Crtp<IMPL_SRC>& matrix_src)
  {
    using matrix_dest_element_type = decltype(lambda(matrix_src(0, 0)));

    auto matrix_dest = create_default_storable(type_v<matrix_dest_element_type>, matrix_src.impl());

    inplace_map(lambda, matrix_dest, matrix_src);

    return matrix_dest;
  }

}
