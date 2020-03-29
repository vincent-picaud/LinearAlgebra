//
// ==, != <= etc... operators
//
#pragma once

#include "LinearAlgebra/dense/vector_scan.hpp"

namespace LinearAlgebra
{
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator==(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return scan_while(
        [](const auto& vector_0_component, const auto& vector_1_component) {
          return vector_0_component == vector_1_component;
        },
        vector_0, vector_1);
  }

}
