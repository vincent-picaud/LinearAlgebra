#pragma once

#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

namespace LinearAlgebra
{
  // Check if this is the same vector representation (= same data)
  template <typename IMPL_0, typename IMPL_1>
  static inline bool
  is_same(const Dense_Vector_Crtp<IMPL_0>& vector_0, const Dense_Vector_Crtp<IMPL_1>& vector_1) noexcept
  {
    if constexpr (std::is_same_v<Element_Type_t<IMPL_0>, Element_Type_t<IMPL_1>>)
    {
      if (vector_0.data() == vector_1.data() and vector_0.size() == vector_1.size() and
          vector_0.increment() == vector_1.increment())
      {
        return true;
      }
    }

    return false;
  }

  // TODO:
  // - is_same vector + matrix
  // - create V_assign_V + matrix
  // - modify op= for V and M

}
