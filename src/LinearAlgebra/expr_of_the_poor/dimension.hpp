// Role: provides functions to check operand dimensions
//
#pragma once
  
#include "LinearAlgebra/dense/matrix_crtp.hpp"

namespace LinearAlgebra
{
  template <typename I_SIZE, typename J_SIZE>
  struct Matrix_Dimension
  {
    I_SIZE _I_size;
    J_SIZE _J_size;
  };

  template <typename IMPL>
  Matrix_Dimension<typename IMPL::I_size_type, typename IMPL::J_size_type>
  dimension(const Matrix_Crtp<IMPL>& M)
  {
    using return_type = decltype(dimension(M));
    return return_type{._I_size = M.I_size(), ._J_size = M.J_size()};
  }
}
