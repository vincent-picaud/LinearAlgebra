//
// CAVEAT: keep sync with matrix_map.hpp
//
#pragma once

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_create_default_storable.hpp"
#include "LinearAlgebra/meta/size_utils.hpp"

namespace LinearAlgebra
{
  template <typename LAMBDA, typename IMPL_SRC, typename... IMPL_SRC_OPTIONAL>
  auto
  map(const LAMBDA& lambda, const Dense_Vector_Crtp<IMPL_SRC>& vector_src,
      const Dense_Vector_Crtp<IMPL_SRC_OPTIONAL>&... vector_src_optional)
  {
    using vector_dest_element_type =
        decltype(lambda(vector_src.as_const()[0], vector_src_optional.as_const()[0]...));
    auto vector_dest = create_default_storable(type_v<vector_dest_element_type>, vector_src,
                                               vector_src_optional...);

    //----------------

    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector_dest[i] = lambda(vector_src.as_const()[i], vector_src_optional.as_const()[i]...);
    };

    // Note: create_default_storable() has already selected
    //       vector_dest with a static size (if possible) hence we can
    //       use vector_dest for loop_over_indices().
    // CAVEAT: we will have to modify/adapt this when vector_src is sparse
    vector_dest.storage_scheme().loop_over_indices(loop_over_indices_lambda);

    return vector_dest;
  }

}
