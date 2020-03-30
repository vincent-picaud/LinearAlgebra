//
// ==, != <= etc... operators
//
// CAVEAT: do not define >= as !< (for array).
//
// Reason: if you do so you will have:
//    (1)  (1,1) <  (1,1)  FALSE
//         but, if >= is !<
//    (2)  (1,0) >= (1,1) TRUE <- which is NOT what we expect
//
//    (1)  (a0 < b0) and (a1 < b1)
// but !(1) is
//    (2)  (a0 >= b0) or (a1 >= b1) (but we want (a0 >= b0) _AND_ (a1 >= b1))
//
#pragma once

#include "LinearAlgebra/dense/vector_scan.hpp"

namespace LinearAlgebra
{
  // note: if sizes are different -> assert failure
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator==(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return scan_while(
        [](const auto& vector_0_component, const auto& vector_1_component) {
          return vector_0_component == vector_1_component;
        },
        vector_0.impl(), vector_1.impl());
  }
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator!=(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return not(vector_0 == vector_1);
  }

  template <typename IMPL_0, typename IMPL_1>
  bool
  operator<(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return scan_while(
        [](const auto& vector_0_component, const auto& vector_1_component) {
          return vector_0_component < vector_1_component;
        },
        vector_0.impl(), vector_1.impl());
  }
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator>(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return scan_while(
        [](const auto& vector_0_component, const auto& vector_1_component) {
          return vector_0_component > vector_1_component;
        },
        vector_0.impl(), vector_1.impl());
  }
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator<=(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return scan_while(
        [](const auto& vector_0_component, const auto& vector_1_component) {
          return vector_0_component <= vector_1_component;
        },
        vector_0.impl(), vector_1.impl());
  }
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator>=(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1)
  {
    return scan_while(
        [](const auto& vector_0_component, const auto& vector_1_component) {
          return vector_0_component >= vector_1_component;
        },
        vector_0.impl(), vector_1.impl());
  }
}
