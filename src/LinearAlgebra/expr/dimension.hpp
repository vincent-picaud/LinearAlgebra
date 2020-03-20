// Role: provides functions to compute and check operand dimensions
//       validity
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  ////////////////////////////////
  // Matrix_Dimension_Predicate //
  ////////////////////////////////

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

  template <typename I0_SIZE, typename J0_SIZE, typename I1_SIZE, typename J1_SIZE>
  Matrix_Dimension_Predicate<I0_SIZE, J1_SIZE> operator*(
      const Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>& M0_dimension,
      const Matrix_Dimension_Predicate<I1_SIZE, J1_SIZE>& M1_dimension) noexcept
  {
    if (M0_dimension and M1_dimension and M0_dimension.J_size() == M1_dimension.I_size())
    {
      return {M0_dimension.I_size(), M1_dimension.J_size()};
    }
    return {};
  }

  template <Matrix_Unary_Op_Enum OP, typename I0_SIZE, typename J0_SIZE>
  auto
  matrix_op(const _matrix_unary_op_t_<OP> op,
            const Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>& dim) noexcept
  {
    if constexpr (does_it_transpose_matrix_dimension(op))
      return Matrix_Dimension_Predicate<J0_SIZE, I0_SIZE>{dim.J_size(), dim.I_size()};
    else
      return Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>{dim.I_size(), dim.J_size()};
  }

  // TODO: chose static size if any (here we systematically chose the first one).
  template <typename I0_SIZE, typename J0_SIZE, typename I1_SIZE, typename J1_SIZE>
  Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>
  operator+(const Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>& M0_dimension,
            const Matrix_Dimension_Predicate<I1_SIZE, J1_SIZE>& M1_dimension) noexcept
  {
    if (M0_dimension and M1_dimension and M0_dimension.I_size() == M1_dimension.I_size() and
        M0_dimension.J_size() == M1_dimension.J_size())
    {
      return {M0_dimension.I_size(), M0_dimension.J_size()};
    }
    return {};
  }

  template <typename I0_SIZE, typename J0_SIZE, typename I1_SIZE, typename J1_SIZE>
  bool
  operator==(const Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>& M0_dimension,
             const Matrix_Dimension_Predicate<I1_SIZE, J1_SIZE>& M1_dimension) noexcept
  {
    if (M0_dimension and M1_dimension and M0_dimension.I_size() == M1_dimension.I_size() and
        M0_dimension.J_size() == M1_dimension.J_size())
    {
      return true;
    }
    return false;
  }

  ////////////////////////////////
  // Vector_Dimension_Predicate //
  ////////////////////////////////

  template <typename SIZE>
  class Vector_Dimension_Predicate
  {
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<SIZE>);

   public:
    using size_type = SIZE;

   private:
    size_type _size;
    bool _is_valid;

   public:
    Vector_Dimension_Predicate() noexcept : _size{}, _is_valid{false} {}
    Vector_Dimension_Predicate(const size_type size) noexcept : _size{size}, _is_valid{true} {}

    operator bool() const noexcept { return _is_valid; }

    size_type
    size() const noexcept
    {
      assert(*this);
      return _size;
    }
  };

  template <typename IMPL>
  Vector_Dimension_Predicate<typename IMPL::size_type>
  dimension_predicate(const Vector_Crtp<IMPL>& V)
  {
    using return_type = decltype(dimension_predicate(V));
    return return_type{V.size()};
  }

  // TODO: chose static size if any (here we systematically chose the first one).
  template <typename SIZE0, typename SIZE1>
  Vector_Dimension_Predicate<SIZE0>
  operator+(const Vector_Dimension_Predicate<SIZE0>& V0_dimension,
            const Vector_Dimension_Predicate<SIZE1>& V1_dimension) noexcept
  {
    if (V0_dimension and V1_dimension and V0_dimension.size() == V1_dimension.size())
    {
      return {V0_dimension.size()};
    }
    return {};
  }

  template <typename SIZE0, typename SIZE1>
  bool
  operator==(const Vector_Dimension_Predicate<SIZE0>& V0_dimension,
             const Vector_Dimension_Predicate<SIZE1>& V1_dimension) noexcept
  {
    if (V0_dimension and V1_dimension and V0_dimension.size() == V1_dimension.size())
    {
      return true;
    }
    return false;
  }

  // Matrix.Vector
  //////////////////////////////////////////////////////////////////
  //
  template <typename I0_SIZE, typename J0_SIZE, typename SIZE>
  Vector_Dimension_Predicate<I0_SIZE> operator*(
      const Matrix_Dimension_Predicate<I0_SIZE, J0_SIZE>& M0_dimension,
      const Vector_Dimension_Predicate<SIZE>& V_dimension) noexcept
  {
    if (M0_dimension and V_dimension and M0_dimension.J_size() == V_dimension.size())
    {
      return {M0_dimension.I_size()};
    }
    return {};
  }

}
