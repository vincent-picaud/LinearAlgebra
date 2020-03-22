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

  // Note: we are constrained to filter arguments by a two-steps approach, otherwise calling
  //
  // create_view(v,1,2)
  //
  // gives BEGIN=int, END=int
  //
  // Hopefully as soon as either one of BEGIN or END is of type size_t
  // the size is dynamic, hence the initial 4 cases:
  //
  // BEGIN                                       | END
  // std::integral_constant<std::size_t, BEGIN>  | std::integral_constant<std::size_t, END>
  // std::integral_constant<std::size_t, BEGIN>  | std::size_t
  // std::size_t                                 | std::integral_constant<std::size_t, END>
  // std::size_t                                 | std::size_t
  //
  // reduces to 2 cases:
  //
  //   1/ both   BEGIN, END are std::integral_constant<std::size_t, ... >
  //
  //   2/ one of BEGIN, END is std::size_t
  //
  namespace Detail
  {
    template <typename IMPL, typename BEGIN, typename END>
    auto
    create_view(Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin, const END end) noexcept
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
    create_view(const Dense_Vector_Crtp<IMPL>& vector, const BEGIN begin, const END end) noexcept
    {
      assert(check_size_begin_end_p(vector.size(), begin, end));

      auto size = compute_size_from_begin_end(begin, end);

      return Default_Vector_Const_View<typename IMPL::element_type, decltype(size),
                                       typename IMPL::increment_type>(
          &vector[begin], size,  // CAVEAT: and not data()+begin
          vector.increment());   //         which does not take into account increment
    }
  }

  template <typename IMPL, std::size_t BEGIN, std::size_t END>
  auto
  create_view(Dense_Vector_Crtp<IMPL>& vector,
              const std::integral_constant<std::size_t, BEGIN> begin,
              const std::integral_constant<std::size_t, END> end) noexcept
  {
    return Detail::create_view(vector, begin, end);
  }
  template <typename IMPL>
  auto
  create_view(Dense_Vector_Crtp<IMPL>& vector, const std::size_t begin,
              const std::size_t end) noexcept
  {
    return Detail::create_view(vector, begin, end);
  }
  // Const versions
  template <typename IMPL, std::size_t BEGIN, std::size_t END>
  auto
  create_view(const Dense_Vector_Crtp<IMPL>& vector,
              const std::integral_constant<std::size_t, BEGIN> begin,
              const std::integral_constant<std::size_t, END> end) noexcept
  {
    return Detail::create_view(vector, begin, end);
  }
  template <typename IMPL>
  auto
  create_view(const Dense_Vector_Crtp<IMPL>& vector, const std::size_t begin,
              const std::size_t end) noexcept
  {
    return Detail::create_view(vector, begin, end);
  }
}
