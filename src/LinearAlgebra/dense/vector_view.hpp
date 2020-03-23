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
    // -> maybe to move elsewhere as this will be reused later
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
    //
    constexpr bool
    check_size_begin_end_p(const std::size_t size, const std::size_t begin,
                           const std::size_t end) noexcept
    {
      bool ok = true;
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

    constexpr std::size_t
    compute_size_from_begin_end(const std::size_t begin, const std::size_t end) noexcept
    {
      assert(begin <= end);

      return end - begin;
    }
    template <std::size_t BEGIN, std::size_t END>
    constexpr std::integral_constant<std::size_t, END - BEGIN>
    compute_size_from_begin_end(const std::integral_constant<std::size_t, BEGIN>,
                                const std::integral_constant<std::size_t, END>) noexcept
    {
      static_assert(BEGIN <= END);

      return {};
    }
  }

  namespace Detail
  {
    /////////////////////////
    // Vector views DETAIL //
    /////////////////////////

    //
    // Most versatile routine that uses all the arguments
    //
    // Note: use size_type_normalization() before calling me
    //
    template <typename ELEMENT_TYPE, typename SIZE, typename INCREMENT>
    auto
    create_view_vector_helper(ELEMENT_TYPE* data, const SIZE size,
                              const INCREMENT increment) noexcept
    {
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<SIZE>);
      static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT>);
      assert(increment > 0);

      if constexpr (std::is_const_v<ELEMENT_TYPE>)
      {
        return Default_Vector_Const_View<std::remove_const_t<ELEMENT_TYPE>, SIZE, INCREMENT>(
            data, size, increment);
      }
      else
      {
        return Default_Vector_View<ELEMENT_TYPE, SIZE, INCREMENT>(data, size, increment);
      }
    }
  }  // Detail

  ////////////////////////////////////////////////////
  // Create view from a raw pointer: user interface //
  ////////////////////////////////////////////////////
  //
  // Note: no need for "const" specialization
  //
  // ELEMENT_TYPE is automatically set to "const element_type" and do
  // the job
  //
  template <typename ELEMENT_TYPE, typename SIZE, typename INCREMENT>
  auto
  create_vector_view(ELEMENT_TYPE* data, const SIZE size, const INCREMENT increment)
  {
    return Detail::create_view_vector_helper(data, Detail::size_type_normalization(size),
                                             Detail::size_type_normalization(increment));
  }
  template <typename ELEMENT_TYPE, typename SIZE>
  auto
  create_vector_view(ELEMENT_TYPE* data, const SIZE size)
  {
    return create_vector_view(data, size, std::integral_constant<std::size_t, 1>());
  }

  /////////////////////////////////////
  // User interface: subvector views //
  /////////////////////////////////////
  //
  template <typename IMPL, typename BEGIN, typename END>
  auto
  create_view_subvector(Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin, const END end) noexcept
  {
    assert(Detail::check_size_begin_end_p(vector.size(), begin, end));

    auto size = Detail::compute_size_from_begin_end(begin, end);

    return Detail::create_view_vector_helper(
        &vector[begin],  // CAVEAT: and not data()+begin
        //                          which does not take into account increment
        size, vector.increment());
  }
  // const version
  template <typename IMPL, typename BEGIN, typename END>
  auto
  create_view_subvector(const Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin,
                        const END end) noexcept
  {
    assert(Detail::check_size_begin_end_p(vector.size(), begin, end));

    auto size = Detail::compute_size_from_begin_end(begin, end);

    return Detail::create_view_vector_helper(
        &vector[begin],  // CAVEAT: and not data()+begin
                         //                          which does not take into account increment
        size, vector.increment());
  }

}
