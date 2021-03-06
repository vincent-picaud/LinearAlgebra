#pragma once

#include <array>
#include <type_traits>
#include <vector>
#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

namespace LinearAlgebra
{
  namespace Detail
  {
    // Note: can be replaced by "concept" or by using a Crtp static
    //       interface. The tag approach as the advantage of using
    //       less boilerplate code
    //
    // Note: this tag must be inherited by _all_ memory chunk classes.
    //
    struct Memory_Chunk_Tag
    {
    };

    template <typename MEMORY_CHUNK>
    constexpr auto Is_Memory_Chunk_v = std::is_base_of_v<Memory_Chunk_Tag, MEMORY_CHUNK>;
  }  // namespace Detail

  template <typename T, typename CAPACITY_TYPE>
  class Default_Memory_Chunk;

  template <typename T, std::size_t N>
  class Default_Memory_Chunk<T, std::integral_constant<std::size_t, N>>
      : public Detail::Memory_Chunk_Tag
  {
    static_assert(not std::is_const_v<T>);

   public:
    using capacity_type = std::integral_constant<std::size_t, N>;
    using element_type  = T;

   protected:
    std::array<T, N> _data;

   public:
    constexpr Default_Memory_Chunk() noexcept = default;
    constexpr Default_Memory_Chunk(const capacity_type ) noexcept {}
    // try to avoid this one as it assume how data is stored...
    constexpr Default_Memory_Chunk(const std::array<T, N>& data) noexcept : _data(data) {}
    constexpr capacity_type
    capacity() const noexcept
    {
      return {};
    }

    constexpr element_type*
    data() noexcept
    {
      return _data.data();
    }
    constexpr const element_type*
    data() const noexcept
    {
      return _data.data();
    }
  };

  template <typename T>
  class Default_Memory_Chunk<T, std::size_t> : public Detail::Memory_Chunk_Tag
  {
    static_assert(not std::is_const_v<T>);

   public:
    using capacity_type = std::size_t;
    using element_type  = T;

   protected:
    std::vector<T> _data;

   public:
    Default_Memory_Chunk() noexcept = default;
    Default_Memory_Chunk(const capacity_type capacity) : _data(capacity) {}
    // try to avoid this one as it assume how data is stored...
    Default_Memory_Chunk(const std::vector<T>& data) : _data(data) {}
    Default_Memory_Chunk(std::vector<T>&& data) noexcept : _data(std::move(data)) {}

    capacity_type
    capacity() const noexcept
    {
      return _data.size();
    }

    element_type*
    data() noexcept
    {
      return _data.data();
    }
    const element_type*
    data() const noexcept
    {
      return _data.data();
    }
  };

  //================================================================

  // Note: for views as we store the same raw pointer type for dynamic
  //       & static cases, not need for specialization
  //
  template <typename T, typename CAPACITY_TYPE>
  class View_Default_Memory_Chunk : public Detail::Memory_Chunk_Tag
  {
    static_assert(not std::is_const_v<T>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<CAPACITY_TYPE>);

   public:
    using capacity_type = CAPACITY_TYPE;
    using element_type  = T;

   protected:
    T* _data;
    capacity_type _capacity;

   public:
    // Note: can be removed if required, for the moment this is only a
    //       safeguard to be sure that dangling views are not created
    //
    View_Default_Memory_Chunk() = delete;
    constexpr View_Default_Memory_Chunk(T* data, capacity_type capacity) noexcept
        : _data(data), _capacity(capacity)
    {
    }

    constexpr capacity_type
    capacity() const noexcept
    {
      return _capacity;
    }

    constexpr element_type*
    data() noexcept
    {
      return _data;
    }
    constexpr const element_type*
    data() const noexcept
    {
      return _data;
    }
  };

  //----------------------------------------------------------------

  // Note: for views as we store the same raw pointer type for dynamic
  //       & static cases, not need for specialization
  //
  template <typename T, typename CAPACITY_TYPE>
  class Const_View_Default_Memory_Chunk : public Detail::Memory_Chunk_Tag
  {
    static_assert(not std::is_const_v<T>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<CAPACITY_TYPE>);

   public:
    using capacity_type = CAPACITY_TYPE;
    using element_type  = T;

   protected:
    const T* _data;
    capacity_type _capacity;

   public:
    // Note: can be removed if required, for the moment this is only a
    //       safeguard to be sure that dangling views are not created
    //
    Const_View_Default_Memory_Chunk() = delete;

    constexpr Const_View_Default_Memory_Chunk(const T* data, capacity_type capacity) noexcept
        : _data(data), _capacity(capacity)
    {
    }

    constexpr capacity_type
    capacity() const noexcept
    {
      return _capacity;
    }

    constexpr const element_type*
    data() noexcept
    {
      return _data;
    }
    constexpr const element_type*
    data() const noexcept
    {
      return _data;
    }
  };

}  // namespace LinearAlgebra
