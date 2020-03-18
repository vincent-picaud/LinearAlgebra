#pragma once

#include "LinearAlgebra/dense/vector.hpp"

namespace LinearAlgebra
{
  template <typename IMPL_DEST, typename IMPL_SRC, typename LAMBDA>
  void
  map(Default_Vector_Crtp<IMPL_DEST>& v_dest, const Default_Vector_Crtp<IMPL_SRC>& v_src,
      const LAMBDA& lambda)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      v_dest[i] = lambda(v_src.as_const()[i]);
    };
    v_dest.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  template <typename IMPL_SRC, typename LAMBDA>
  auto
  map(const Default_Vector_Crtp<IMPL_SRC>& v_src, const LAMBDA& lambda)
  {
    using v_dest_type = Default_Vector<decltype(lambda(v_src[0])), typename IMPL_SRC::size_type,
                                       std::integral_constant<std::size_t, 1>>;
    v_dest_type v_dest(v_src.size());

    map(v_dest, v_src, lambda);

    return v_dest;
  }

}
