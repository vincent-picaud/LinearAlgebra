// Role: provides functions to check operand dimensions
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/meta/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  template <typename I_SIZE, typename J_SIZE>
  class Matrix_Dimension
  {
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<I_SIZE> and
                  Is_Std_Integral_Constant_Size_Or_Std_Size_v<J_SIZE>);

   public:
    using I_size_type = I_SIZE;
    using J_size_type = J_SIZE;

   private:
    I_size_type _I_size;
    J_size_type _J_size;

   public:
    Matrix_Dimension(I_size_type I_size, J_size_type J_size) : _I_size{I_size}, _J_size{J_size} {}

    I_size_type
    I_size() const noexcept
    {
      return _I_size;
    };
    J_size_type
    J_size() const noexcept
    {
      return _J_size;
    };
  };

  template <typename IMPL>
  Matrix_Dimension<typename IMPL::I_size_type, typename IMPL::J_size_type>
  dimension(const Matrix_Crtp<IMPL>& M)
  {
    using return_type = decltype(dimension(M));
    return return_type{M.I_size(), M.J_size()};
  }
}
