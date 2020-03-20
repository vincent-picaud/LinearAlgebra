//
// CAVEAT: keep sync with vector_fill.hpp
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

namespace LinearAlgebra
{
  //
  // V[i]=lambda()
  //
  template <typename LAMBDA, typename IMPL>
  void
  fill(const LAMBDA& lambda, Dense_Vector_Crtp<IMPL>& vector)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) { vector[i] = lambda(); };
    vector.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }

  //
  // V[i]=lambda(i)
  //
  template <typename LAMBDA, typename IMPL>
  void
  fill_indexed(const LAMBDA& lambda, Dense_Vector_Crtp<IMPL>& vector)
  {
    const auto loop_over_indices_lambda = [&](const std::size_t i) { vector[i] = lambda(i); };
    vector.storage_scheme().loop_over_indices(loop_over_indices_lambda);
  }
}
