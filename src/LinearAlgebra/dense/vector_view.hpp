// Role: create vector views
//
// CAVEAT: for views our convention is *always* to use [begin,end[ and NOT (begin,size)
//         by example create_view(2,4) mean {v_2,v_3}, begin=2, end=4 (and NOT {v_2,v_3,v_4,v_5}, begin=2, size=4))
//
#pragma once

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    // Some utils
    //////////////////////////////////////////////////////////////////
    //
    // -> a priori to move elsewhere as this will be reused later
    //
    template <typename BEGIN, typename END>
    bool
    check_size_begin_end_p(const std::size_t size, const BEGIN begin, const END end) noexcept
    {
      bool ok = true;
      ok &= Is_Std_Integral_Constant_Size_Or_Std_Size_v<BEGIN>;
      ok &= Is_Std_Integral_Constant_Size_Or_Std_Size_v<END>;
      ok &= 0 <= begin;
      ok &= begin <= end;
      ok &= end <= size;
      return ok;
    }

    //================================================================

    // Implicit conversion
    constexpr std::size_t
    size_type_normalization(const std::size_t size) noexcept
    {
      return size;
    }

    template <std::size_t SIZE>
    constexpr std::integral_constant<std::size_t, SIZE>
    size_type_normalization(const std::integral_constant<std::size_t, SIZE>) noexcept
    {
      return {};
    }

    //================================================================

    std::size_t
    compute_size_from_begin_end(const std::size_t begin, const std::size_t end) noexcept
    {
      assert(begin <= end);

      return end - begin;
    }
    template <std::size_t BEGIN, std::size_t END>
    std::integral_constant<std::size_t, END - BEGIN>
    compute_size_from_begin_end(const std::integral_constant<std::size_t, BEGIN>,
                                const std::integral_constant<std::size_t, END>) noexcept
    {
      static_assert(BEGIN <= END);

      return {};
    }
  }

  // Vector views
  //////////////////////////////////////////////////////////////////
  //

  // Note: we are constrained to insure that create_view() size argument types are either:
  //
  // - std::size_t
  // - std::integral_constant<std::size_t, ... >
  //
  // This is the role of size_type_normalization() functions.
  //
  // Then we have to use a two-steps approach:
  //
  //   1. a *user* create_view<BEGIN,END>(...) interface where
  //   possibly BEGIN=int, END=int In this *user* function,
  //   size_type_normalization() is used to only produce std::size_t
  //   or std::integral_constant<std::size_t, ... >
  //
  //   2. a call to Detail::create_view(...) is then performed with
  //   using the transformed type.
  //
  // CAVEAT: as a side effect, like *user* interfaces do not control
  //         template parameter *types* anymore, we must avoid name
  //         collision. To disambiguate all the possible view types we
  //         use different function *names*. By example the generic
  //         "create_view()" function name have been declined into
  //         variants like: create_view_subvector(), create_view_XXX
  //         etc....
  //
  namespace Detail
  {
    // Note: use size_type_normalization() before calling me
    template <typename IMPL, typename BEGIN, typename END>
    auto
    create_view_vector_helper(Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin,
                              const END end) noexcept
    {
      assert(check_size_begin_end_p(vector.size(), begin, end));

      auto size = compute_size_from_begin_end(begin, end);

      return Default_Vector_View<typename IMPL::element_type, decltype(size),
                                 typename IMPL::increment_type>(
          &vector[begin], size,  // CAVEAT: and not data()+begin
          vector.increment());   //         which does not take into account increment
    }
    // Const version is identical except:
    //
    //  1/ the "const" declaration of the "vector" argument
    //
    //  2/ the returned const view
    //
    template <typename IMPL, typename BEGIN, typename END>
    auto
    create_view_vector_helper(const Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin,
                              const END end) noexcept
    {
      assert(check_size_begin_end_p(vector.size(), begin, end));

      auto size = compute_size_from_begin_end(begin, end);

      return Default_Vector_Const_View<typename IMPL::element_type, decltype(size),
                                       typename IMPL::increment_type>(
          &vector[begin], size,  // CAVEAT: and not data()+begin
          vector.increment());   //         which does not take into account increment
    }
  }

  // User interface
  //
  template <typename IMPL, typename BEGIN, typename END>
  auto
  create_view_subvector(Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin, const END end) noexcept
  {
    return Detail::create_view_vector_helper(vector, Detail::size_type_normalization(begin),
                                             Detail::size_type_normalization(end));
  }
  // const version
  template <typename IMPL, typename BEGIN, typename END>
  auto
  create_view_subvector(const Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin,
                        const END end) noexcept
  {
    return Detail::create_view_vector_helper(vector, Detail::size_type_normalization(begin),
                                             Detail::size_type_normalization(end));
  }
}
