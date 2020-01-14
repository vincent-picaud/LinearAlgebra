#pragma once

#include <array>
#include <type_traits>
#include "LinearAlgebra/meta/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    // substitute to partial specializations
    //
    template <typename INCREMENT>
    constexpr auto
    increment_default_value_helper()
    {
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT>);

      if constexpr (std::is_same_v<std::size_t, INCREMENT>)
      {
        return 1;
      }
      else
      {
        return INCREMENT();  // the initial integral_constant
      }
    }

    // substitute to partial specializations
    //
    template <typename N_TYPE, typename INCREMENT>
    constexpr auto
    vector_required_capacity_helper(const N_TYPE n, const INCREMENT inc)
    {
      return (n == 0) ? 0 : (n - 1) * inc + 1;
    }
    template <size_t N, size_t INCREMENT>
    constexpr auto
    vector_required_capacity_helper(const std::integral_constant<size_t, N>,
                                    const std::integral_constant<size_t, INCREMENT>)
    {
      return std::integral_constant<size_t, vector_required_capacity_helper(N, INCREMENT)>();
    }

    template <typename N_TYPE, typename INCREMENT>
    using vector_required_capacity_helper_t = decltype(
        vector_required_capacity_helper(std::declval<N_TYPE>(), std::declval<INCREMENT>()));
  }

  template <typename N_TYPE, typename INCREMENT>
  class Default_Vector_Storage_Scheme
  {
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<N_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT>);

   public:
    using required_capacity_type = Detail::vector_required_capacity_helper_t<N_TYPE, INCREMENT>;

    using size_type = N_TYPE;

    using increment_type = INCREMENT;

   protected:
    N_TYPE _n;
    INCREMENT _inc;

   public:
    constexpr Default_Vector_Storage_Scheme() : _n(), _inc() {}

    constexpr Default_Vector_Storage_Scheme(const N_TYPE n, const INCREMENT inc) : _n(n), _inc(inc)
    {
      assert(_inc > 0);
    }
    constexpr Default_Vector_Storage_Scheme(const N_TYPE n)
        : Default_Vector_Storage_Scheme(n, Detail::increment_default_value_helper<INCREMENT>())
    {
    }

    constexpr required_capacity_type
    required_capacity() const
    {
      return Detail::vector_required_capacity_helper(_n, _inc);
    }
    constexpr size_type
    size() const
    {
      return _n;
    }

    constexpr increment_type
    increment() const
    {
      return _inc;
    }

    constexpr bool
    check_index(const size_t i) const
    {
      return i < _n;
    };

    constexpr size_t
    offset(const size_t i) const
    {
      return i * _inc;
    }

    template <typename LAMBDA>
    void
    loop_over_indices(const LAMBDA& lambda) const
    {
      for (size_t i = 0; i < _n; ++i)
      {
        lambda(i);
      }
    }
  };

  //================================================================

  template <typename N_0_TYPE, typename INCREMENT_0_INCREMENT, typename N_1_TYPE,
            typename INCREMENT_1_INCREMENT>
  constexpr bool
  are_compatibles(
      const Default_Vector_Storage_Scheme<N_0_TYPE, INCREMENT_0_INCREMENT>& vector_storage_0,
      const Default_Vector_Storage_Scheme<N_1_TYPE, INCREMENT_1_INCREMENT>& vector_storage_1)
  {
    return vector_storage_0.size() == vector_storage_1.size();
  }
}
