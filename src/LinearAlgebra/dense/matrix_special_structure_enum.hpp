#pragma once

#include <type_traits>

namespace LinearAlgebra
{
  enum class Matrix_Special_Structure_Enum
  {
    None,
    Symmetric,
    Hermitian,
    Triangular,
    Unit_Triangular,
    Triangular_Strict
  };

  template <Matrix_Special_Structure_Enum CATEGORY>
  struct Matrix_Special_Structure_Imposes_Square_Matrix
      : std::conditional_t<CATEGORY == Matrix_Special_Structure_Enum::Symmetric or
                               CATEGORY == Matrix_Special_Structure_Enum::Hermitian,
                           std::true_type,
                           std::false_type>
  {
  };

}
