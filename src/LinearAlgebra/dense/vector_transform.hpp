//
// CAVEAT: keep sync with matrix_transform.hpp
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

namespace LinearAlgebra
{
  //
  // V[i]=lambda(V[i])
  //
  template <typename IMPL, typename LAMBDA>
  void
  transform(Dense_Vector_Crtp<IMPL>& vector, const LAMBDA& lambda)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector[i] = lambda(vector.as_const()[i]);
    };
    vector.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  //
  // V[i]=lambda(V[i],i)
  //
  template <typename IMPL, typename LAMBDA>
  void
  transform_indexed(Dense_Vector_Crtp<IMPL>& vector, const LAMBDA& lambda)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector[i] = lambda(vector.as_const()[i], i);
    };
    vector.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }
}
