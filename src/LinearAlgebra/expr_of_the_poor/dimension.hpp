// Role: provides functions to check operand dimensions
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/meta/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  template <typename I_SIZE, typename J_SIZE>
  class Matrix_Dimension_Predicate
  {
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<I_SIZE> and
                  Is_Std_Integral_Constant_Size_Or_Std_Size_v<J_SIZE>);

   public:
    using I_size_type = I_SIZE;
    using J_size_type = J_SIZE;

   private:
    I_size_type _I_size;
    J_size_type _J_size;
    bool _is_valid;

   public:
    Matrix_Dimension_Predicate() noexcept : _I_size{}, _J_size{}, _is_valid{false} {}
    Matrix_Dimension_Predicate(const I_size_type I_size, const J_size_type J_size) noexcept
        : _I_size{I_size}, _J_size{J_size}, _is_valid{true}
    {
    }

    operator bool() const noexcept { return _is_valid; }

    I_size_type
    I_size() const noexcept
    {
      assert(*this);
      return _I_size;
    }

    J_size_type
    J_size() const noexcept
    {
      assert(*this);
      return _J_size;
    }
  };

  template <typename IMPL>
  Matrix_Dimension_Predicate<typename IMPL::I_size_type, typename IMPL::J_size_type>
  dimension_predicate(const Matrix_Crtp<IMPL>& M)
  {
    using return_type = decltype(dimension_predicate(M));
    return return_type{M.I_size(), M.J_size()};
  }

}
