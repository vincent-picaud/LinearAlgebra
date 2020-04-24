//
// CAVEAT: keep sync with vector_map.hpp
//
#pragma once

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/matrix_similar.hpp"

namespace LinearAlgebra
{
  template <typename LAMBDA, typename IMPL_SRC, typename... IMPL_SRC_OPTIONAL>
  auto
  map(const LAMBDA& lambda,
      const Dense_Matrix_Crtp<IMPL_SRC>& matrix_src,
      const Dense_Matrix_Crtp<IMPL_SRC_OPTIONAL>&... matrix_src_optional)
  {
    using matrix_dest_element_type =
        decltype(lambda(matrix_src.as_const()(0, 0), matrix_src_optional.as_const()(0, 0)...));
    auto matrix_dest = similar(Type_v<matrix_dest_element_type>, matrix_src.impl());

    //----------------

    const auto loop_over_indices_lambda = [&](const std::size_t i, const std::size_t j) {
      matrix_dest(i, j) = lambda(matrix_src.as_const()(i, j));
    };
    // Note: similar() has already selected
    //       matrix_dest with a static size (if possible) hence we can
    //       use matrix_dest for loop_over_indices().
    // CAVEAT: we will have to modify/adapt this when matrix_src is sparse
    matrix_dest.storage_scheme().loop_over_indices(loop_over_indices_lambda);

    return matrix_dest;
  }

}
