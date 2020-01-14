#pragma once

#include <array>
#include <cassert>
#include <type_traits>
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
    // substitute to partial specializations
    //
    template <typename N_TYPE, typename M_TYPE, typename LEADING_DIMENSION>
    constexpr auto
    matrix_required_capacity_helper(const N_TYPE n, const M_TYPE m, const LEADING_DIMENSION ld)
    {
      return (n == 0 or m == 0) ? 0 : (n - 1) + (m - 1) * ld + 1;
    }
    template <size_t N, size_t M, size_t LEADING_DIMENSION>
    constexpr auto
    matrix_required_capacity_helper(const std::integral_constant<size_t, N>,
                                    const std::integral_constant<size_t, M>,
                                    const std::integral_constant<size_t, LEADING_DIMENSION>)
    {
      return std::integral_constant<size_t,
                                    matrix_required_capacity_helper(N, M, LEADING_DIMENSION)>();
    }

    template <typename N_TYPE, typename M_TYPE, typename LEADING_DIMENSION>
    using matrix_required_capacity_helper_t = decltype(matrix_required_capacity_helper(
        std::declval<N_TYPE>(), std::declval<M_TYPE>(), std::declval<LEADING_DIMENSION>()));

    // substitute to partial specializations
    // -> leading dimension default value helper
    template <typename N_TYPE, size_t LEADING_DIMENSION>
    constexpr auto
    ld_default_value_helper(const N_TYPE n,
                            const std::integral_constant<size_t, LEADING_DIMENSION> ld)
    {
      return ld;
    }

    template <size_t N, size_t LEADING_DIMENSION>
    constexpr auto
    ld_default_value_helper(const std::integral_constant<size_t, N>,
                            const std::integral_constant<size_t, LEADING_DIMENSION> ld)
    {
      return ld;
    }

    template <size_t N>
    constexpr auto
    ld_default_value_helper(const std::integral_constant<size_t, N> n, const size_t ld)
    {
      return n;
    }

    constexpr auto
    ld_default_value_helper(const size_t n, const size_t)
    {
      return n;
    }
  }

  // For the moment we restrict our self to Fortan-Blas like scheme
  // (use Column major storage)
  template <Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix_Storage_Scheme
  {
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<N_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<M_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<LEADING_DIMENSION>);

   public:
    using required_capacity_type =
        Detail::matrix_required_capacity_helper_t<N_TYPE, M_TYPE, LEADING_DIMENSION>;

    using I_size_type = N_TYPE;
    using J_size_type = M_TYPE;

    using leading_dimension_type = LEADING_DIMENSION;

    using matrix_storage_mask_type = std::integral_constant<Matrix_Storage_Mask_Enum, MASK>;

   protected:
    N_TYPE _n;
    M_TYPE _m;
    LEADING_DIMENSION _ld;

   protected:
    constexpr bool
    check_invariant() const
    {
      return _n <= _ld;
    }

   public:
    constexpr Default_Matrix_Storage_Scheme() : _n(), _m(), _ld() { assert(check_invariant()); }

    constexpr Default_Matrix_Storage_Scheme(const N_TYPE n, const M_TYPE m,
                                            const LEADING_DIMENSION ld)
        : _n(n), _m(m), _ld(ld)
    {
      assert(check_invariant());
    }
    constexpr Default_Matrix_Storage_Scheme(const N_TYPE n, const M_TYPE m)
        : Default_Matrix_Storage_Scheme(n, m,
                                        Detail::ld_default_value_helper(n, LEADING_DIMENSION()))
    {
    }

    constexpr required_capacity_type
    required_capacity() const
    {
      return Detail::matrix_required_capacity_helper(_n, _m, _ld);
    }
    constexpr I_size_type
    I_size() const
    {
      return _n;
    }
    constexpr J_size_type
    J_size() const
    {
      return _m;
    }

    constexpr leading_dimension_type
    leading_dimension() const
    {
      return _ld;
    }

    constexpr bool
    check_index(const size_t i, const size_t j) const
    {
      bool ok = i < _n and j < _m;
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

    template <Matrix_Storage_Mask_Enum MASK_OTHER, typename LAMBDA>
    void
    loop_over_indices(const LAMBDA& lambda) const
    {
      switch (MASK_OTHER)
      {
        case Matrix_Storage_Mask_Enum::None:
          for (size_t j = 0; j < _m; ++j)
            for (size_t i = 0; i < _n; ++i) lambda(i, j);
          break;
        case Matrix_Storage_Mask_Enum::Upper:
          for (size_t j = 0; j < _m; ++j)
          {
            const auto i_end = (j + 1 < _n) ? j + 1 : _n;
            for (size_t i = 0; i < i_end; ++i) lambda(i, j);
          }
          break;
        case Matrix_Storage_Mask_Enum::Upper_Strict:
          for (size_t j = 0; j < _m; ++j)
          {
            const auto i_end = (j < _n) ? j : _n;
            for (size_t i = 0; i < i_end; ++i) lambda(i, j);
          }
          break;
        case Matrix_Storage_Mask_Enum::Lower:
          for (size_t j = 0; j < _m; ++j)
            for (size_t i = j; i < _n; ++i) lambda(i, j);
          break;
        case Matrix_Storage_Mask_Enum::Lower_Strict:
          for (size_t j = 0; j < _m; ++j)
            for (size_t i = j + 1; i < _n; ++i) lambda(i, j);
          break;
      }
    }

    template <typename LAMBDA>
    void
    loop_over_indices(const LAMBDA& lambda) const
    {
      loop_over_indices<MASK>(lambda);
    }

    constexpr size_t
    offset(const size_t i, const size_t j) const
    {
      return i + j * _ld;
    }

    // Change MASK type
    template <Matrix_Storage_Mask_Enum MASK_OTHER>
    Default_Matrix_Storage_Scheme<MASK_OTHER, N_TYPE, M_TYPE, LEADING_DIMENSION>
    as() const
    {
      return {_n, _m, _ld};
    }
  };

  //================================================================

  template <Matrix_Storage_Mask_Enum MASK_0, typename N_0_TYPE, typename M_0_TYPE,
            typename LEADING_DIMENSION_0, Matrix_Storage_Mask_Enum MASK_1, typename N_1_TYPE,
            typename M_1_TYPE, typename LEADING_DIMENSION_1>
  constexpr bool
  are_compatibles(const Default_Matrix_Storage_Scheme<MASK_0, N_0_TYPE, M_0_TYPE,
                                                      LEADING_DIMENSION_0>& matrix_storage_0,
                  const Default_Matrix_Storage_Scheme<MASK_1, N_1_TYPE, M_1_TYPE,
                                                      LEADING_DIMENSION_1>& matrix_storage_1)
  {
    return (MASK_0 == MASK_1 and matrix_storage_0.I_size() == matrix_storage_1.I_size() and
            matrix_storage_0.J_size() == matrix_storage_1.J_size());
  }
}
