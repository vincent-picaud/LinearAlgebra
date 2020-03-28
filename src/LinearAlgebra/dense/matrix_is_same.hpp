#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/utils/element_type.hpp"

namespace LinearAlgebra
{
  // Check if this is the same matrix representation (= same data)
  template <typename IMPL_0, typename IMPL_1>
  static inline bool
  is_same(const Dense_Matrix_Crtp<IMPL_0>& matrix_0,
          const Dense_Matrix_Crtp<IMPL_1>& matrix_1) noexcept
  {
    if constexpr (std::is_same_v<Element_Type_t<IMPL_0>, Element_Type_t<IMPL_1>>)
    {
      if (matrix_0.data() == matrix_1.data() and matrix_0.I_size() == matrix_1.I_size() and
          matrix_0.J_size() == matrix_1.J_size() and
          matrix_0.leading_dimension() == matrix_1.leading_dimension())
      {
        return true;
      }
    }

    return false;
  }

}
