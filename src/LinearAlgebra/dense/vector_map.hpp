//
// CAVEAT: keep sync with matrix_map.hpp
//
#pragma once

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_create_default_storable.hpp"

namespace LinearAlgebra
{
  template <typename IMPL_DEST, typename IMPL_SRC, typename LAMBDA>
  void
  inplace_map(Default_Vector_Crtp<IMPL_DEST>& vector_dest,
              const Default_Vector_Crtp<IMPL_SRC>& vector_src, const LAMBDA& lambda)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector_dest[i] = lambda(vector_src.as_const()[i]);
    };
    vector_dest.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  template <typename IMPL_SRC, typename LAMBDA>
  auto
  map(const Default_Vector_Crtp<IMPL_SRC>& vector_src, const LAMBDA& lambda)
  {
    using vector_dest_element_type = decltype(lambda(vector_src[0]));

    auto vector_dest = create_default_storable(type_v<vector_dest_element_type>, vector_src.impl());

    inplace_map(vector_dest, vector_src, lambda);

    return vector_dest;
  }

}
