#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

namespace LinearAlgebra
{
  template <typename IMPL, typename LAMBDA>
  void
  transform(Default_Vector_Crtp<IMPL>& v, const LAMBDA& lambda)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      v[i] = lambda(v.as_const()[i]);
    };
    v.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  template <typename IMPL, typename LAMBDA>
  void
  transform_indexed(Default_Vector_Crtp<IMPL>& v, const LAMBDA& lambda)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      v[i] = lambda(v.as_const()[i], i);
    };
    v.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }
}
