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

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
#ifdef LINALG_CODE
#error
#endif

#define LINALG_CODE(OP)                                                          \
  template <typename IMPL_0, typename IMPL_1>                                    \
  bool operator OP(const VMT_Crtp<IMPL_0>& vmt_0, const VMT_Crtp<IMPL_1>& vmt_1) \
  {                                                                              \
    return scan_while(                                                           \
        [](const auto& vmt_0_component, const auto& vmt_1_component) {           \
          return vmt_0_component OP vmt_1_component;                             \
        },                                                                       \
        vmt_0.impl(),                                                            \
        vmt_1.impl());                                                           \
  }

  LINALG_CODE(==)
  // CAVEAT: not LINALG_CODE(!=); see journal.org ID =
  //         3bb0fbb6-b81f-406b-be4f-640a7f9a4089
  template <typename IMPL_0, typename IMPL_1>
  bool
  operator!=(const VMT_Crtp<IMPL_0>& vmt_0, const VMT_Crtp<IMPL_1>& vmt_1)
  {
    return not(vmt_0 == vmt_1);
  }
  LINALG_CODE(<)
  LINALG_CODE(>)
  LINALG_CODE(<=)
  LINALG_CODE(>=)

#undef LINALG_CODE

  // Scalar mixing: scalar - VMT
#define LINALG_CODE(OP)                                                                           \
  template <typename IMPL_1>                                                                      \
  bool operator OP(const Element_Type_t<IMPL_1>& vmt_0, const VMT_Crtp<IMPL_1>& vmt_1)            \
  {                                                                                               \
    return scan_while([&vmt_0](const auto& vmt_1_component) { return vmt_0 OP vmt_1_component; }, \
                      vmt_1.impl());                                                              \
  }

  LINALG_CODE(==)
  template <typename IMPL_1>
  bool
  operator!=(const Element_Type_t<IMPL_1>& vmt_0, const VMT_Crtp<IMPL_1>& vmt_1)
  {
    return not(vmt_0 == vmt_1);
  }
  LINALG_CODE(<)
  LINALG_CODE(>)
  LINALG_CODE(<=)
  LINALG_CODE(>=)

#undef LINALG_CODE

  // Scalar mixing: VMT - scalar
#define LINALG_CODE(OP)                                                                           \
  template <typename IMPL_0>                                                                      \
  bool operator OP(const VMT_Crtp<IMPL_0>& vmt_0, const Element_Type_t<IMPL_0>& vmt_1)            \
  {                                                                                               \
    return scan_while([&vmt_1](const auto& vmt_0_component) { return vmt_0_component OP vmt_1; }, \
                      vmt_0.impl());                                                              \
  }

  LINALG_CODE(==)
  template <typename IMPL_0>
  bool
  operator!=(const VMT_Crtp<IMPL_0>& vmt_0, const Element_Type_t<IMPL_0>& vmt_1)
  {
    return not(vmt_0 == vmt_1);
  }
  LINALG_CODE(<)
  LINALG_CODE(>)
  LINALG_CODE(<=)
  LINALG_CODE(>=)

#undef LINALG_CODE

}  // namespace LinearAlgebra
