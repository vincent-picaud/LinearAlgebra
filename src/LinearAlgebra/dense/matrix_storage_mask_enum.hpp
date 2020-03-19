//
// Matrix can be define by 2 properties:
//  1. a mask       : Upper, None...
//  2. a matrix type: Triangular, Symmetric...
//
// This enum defines the property 1.
//
// Remark: property 2. is defined in "matrix_special_structure_enum.hpp"
//
#pragma once

#include "LinearAlgebra/meta/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  enum class Matrix_Storage_Mask_Enum
  {
    None,
    Upper,
    Upper_Strict,
    Lower,
    Lower_Strict
  };

  namespace Detail
  {
    // Check index according to Matrix_Storage_Mask_Enum value
    //////////////////////////////////////////////////////////////////
    //
    // CAVEAT: this function does not check if i<I_Size and j<J_size !
    //
    template <Matrix_Storage_Mask_Enum MASK, typename I_INDEX, typename J_INDEX>
    constexpr bool
    check_index(const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>, const I_INDEX i,
                const J_INDEX j) noexcept
    {
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<I_INDEX>);
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<J_INDEX>);

      bool ok = true;
      switch (MASK)
      {
        case Matrix_Storage_Mask_Enum::None:
          break;
        case Matrix_Storage_Mask_Enum::Upper:
          ok &= i <= j;
          break;
        case Matrix_Storage_Mask_Enum::Upper_Strict:
          ok &= i < j;
          break;
        case Matrix_Storage_Mask_Enum::Lower:
          ok &= i >= j;
          break;
        case Matrix_Storage_Mask_Enum::Lower_Strict:
          ok &= i > j;
          break;
      }
      return ok;
    };

    // Loop over indices
    //////////////////////////////////////////////////////////////////
    //
    template <typename LAMBDA, Matrix_Storage_Mask_Enum MASK, typename I_SIZE, typename J_SIZE>
    constexpr void
    loop_over_indices(const LAMBDA& lambda,
                      const std::integral_constant<Matrix_Storage_Mask_Enum, MASK>,
                      const I_SIZE I_size, const J_SIZE J_size)
    {
      switch (MASK)
      {
        case Matrix_Storage_Mask_Enum::None:
          for (size_t j = 0; j < J_size; ++j)
            for (size_t i = 0; i < I_size; ++i) lambda(i, j);
          break;
        case Matrix_Storage_Mask_Enum::Upper:
          for (size_t j = 0; j < J_size; ++j)
          {
            const auto i_end = (j + 1 < I_size) ? j + 1 : I_size;
            for (size_t i = 0; i < i_end; ++i) lambda(i, j);
          }
          break;
        case Matrix_Storage_Mask_Enum::Upper_Strict:
          for (size_t j = 0; j < J_size; ++j)
          {
            const auto i_end = (j < I_size) ? j : I_size;
            for (size_t i = 0; i < i_end; ++i) lambda(i, j);
          }
          break;
        case Matrix_Storage_Mask_Enum::Lower:
          for (size_t j = 0; j < J_size; ++j)
            for (size_t i = j; i < I_size; ++i) lambda(i, j);
          break;
        case Matrix_Storage_Mask_Enum::Lower_Strict:
          for (size_t j = 0; j < J_size; ++j)
            for (size_t i = j + 1; i < I_size; ++i) lambda(i, j);
          break;
      }
    }
  }  // Detail
}
