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
  template <typename LAMBDA, typename IMPL>
  void
  transform(const LAMBDA& lambda,Dense_Vector_Crtp<IMPL>& vector)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector[i] = lambda(vector.as_const()[i]);
    };
    vector.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  //
  // V[i]=lambda(V[i],i)
  //
  template <typename LAMBDA, typename IMPL>
  void
  transform_indexed(const LAMBDA& lambda,Dense_Vector_Crtp<IMPL>& vector)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      vector[i] = lambda(vector.as_const()[i], i);
    };
    vector.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }
}
