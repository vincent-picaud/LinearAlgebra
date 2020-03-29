//
// CAVEAT: keep sync with matrix_transform.hpp
//
#pragma once

#include "LinearAlgebra/dense/vector_are_compatible.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/utils/size_utils.hpp"

namespace LinearAlgebra
{
  //
  // lambda(V[i],Vopt1[i],Vopt2[i]...) everything is const
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  void
  scan(const LAMBDA& lambda, const Dense_Vector_Crtp<IMPL>& vector,
       const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional)
  {
    assert(are_compatible_p(vector, vector_optional...));

    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      lambda(vector[i], vector_optional[i]...);
    };

    // For efficiency, try to catch a static size if any
    auto vector_dest_size = get_static_size_if_any(vector.size(), vector_optional.size()...);

    Detail::loop_over_indices(loop_over_indices_lambda, vector_dest_size);
  }

  //
  // lambda(i,V[i],Vopt1[i],Vopt2[i]...) everything is const
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  void
  scan_indexed(const LAMBDA& lambda, const Dense_Vector_Crtp<IMPL>& vector,
               const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional)
  {
    assert(are_compatible_p(vector, vector_optional...));

    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      lambda(i, vector[i], vector_optional[i]...);
    };
    // For efficiency, try to catch a static size if any
    auto vector_dest_size = get_static_size_if_any(vector.size(), vector_optional.size()...);

    Detail::loop_over_indices(loop_over_indices_lambda, vector_dest_size);
  }

  //////////////////////////////////////////////////////////////////

  //
  // lambda(V[i],Vopt1[i],Vopt2[i]...) everything is const
  //
  // TODO: add also into matrix_scan
  //
  template <typename LAMBDA, typename IMPL, typename... IMPL_OPTIONAL>
  bool
  scan_while(const LAMBDA& lambda, const Dense_Vector_Crtp<IMPL>& vector,
             const Dense_Vector_Crtp<IMPL_OPTIONAL>&... vector_optional)
  {
    assert(are_compatible_p(vector, vector_optional...));

    const auto loop_over_indices_lambda = [&](const std::size_t i) {
      return lambda(vector[i], vector_optional[i]...);
    };

    // For efficiency, try to catch a static size if any
    auto vector_dest_size = get_static_size_if_any(vector.size(), vector_optional.size()...);

    return Detail::loop_over_indices_while(loop_over_indices_lambda, vector_dest_size);
  }
}
