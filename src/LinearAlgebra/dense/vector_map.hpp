//
// CAVEAT: keep sync with matrix_map.hpp
//
#pragma once

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_create_default_storable.hpp"

namespace LinearAlgebra
{
  template <typename LAMBDA, typename IMPL_SRC>
  auto
  map(const LAMBDA& lambda, const Dense_Vector_Crtp<IMPL_SRC>& vector_src)
  {
    using vector_dest_element_type = decltype(lambda(vector_src[0]));
    auto vector_dest = create_default_storable(type_v<vector_dest_element_type>, vector_src.impl());

    //----------------

    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector_dest[i] = lambda(vector_src.as_const()[i]);
    };
    vector_dest.storage_scheme().loop_over_indices(loop_over_indices_lambda);

    return vector_dest;
  }

}
