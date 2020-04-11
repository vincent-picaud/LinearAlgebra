// Check if this two C++ objects represent the same mathematical
// object (=instance representing the same data)
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

#include "LinearAlgebra/utils/element_type.hpp"

#include <type_traits>

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Fall back
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL_0, typename IMPL_1>
  constexpr bool
  same_mathematical_object_p(const Crtp<IMPL_0>& matrix_0, const Crtp<IMPL_1>& matrix_1) noexcept
  {
    return false;
  }

  //////////////////////////////////////////////////////////////////
  // Dense Vector
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL_0, typename IMPL_1>
  constexpr bool
  same_mathematical_object_p(const Dense_Vector_Crtp<IMPL_0>& vector_0,
                             const Dense_Vector_Crtp<IMPL_1>& vector_1) noexcept
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

  //////////////////////////////////////////////////////////////////
  // Dense Matrix
  //////////////////////////////////////////////////////////////////
  //
  template <typename IMPL_0, typename IMPL_1>
  constexpr bool
  same_mathematical_object_p(const Dense_Matrix_Crtp<IMPL_0>& matrix_0,
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
