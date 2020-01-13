#pragma once

#include <array>
#include <type_traits>
#include <vector>
#include "LinearAlgebra/dense/is_std_integral_constant.hpp"

namespace KissDStream
{
  template <typename T, typename CAPACITY_TYPE>
  class Default_Memory_Chunk;

  template <typename T, std::size_t N>
  class Default_Memory_Chunk<T, std::integral_constant<std::size_t, N>>
  {
   public:
    using capacity_type = std::integral_constant<std::size_t, N>;
    using element_type  = T;

   protected:
    std::array<T, N> _data;

   public:
    Default_Memory_Chunk(const capacity_type capacity) {}
    constexpr capacity_type
    capacity() const
    {
      return {};
    }

    constexpr element_type*
    data()
    {
      return _data.data();
    }
    constexpr const element_type*
    data() const
    {
      return _data.data();
    }
  };

  template <typename T>
  class Default_Memory_Chunk<T, std::size_t>
  {
   public:
    using capacity_type = std::size_t;
    using element_type  = T;

   protected:
    std::vector<T> _data;

   public:
    Default_Memory_Chunk(const capacity_type capacity) : _data(capacity) {}
    capacity_type
    capacity() const
    {
      return _data.size();
    }

    element_type*
    data()
    {
      return _data.data();
    }
    const element_type*
    data() const
    {
      return _data.data();
    }
  };

  //================================================================

  // Note: for views as we store the same raw pointer type for dynamic
  // & static cases, not need for specialization
  //
  template <typename T, typename CAPACITY_TYPE>
  class View_Default_Memory_Chunk
  {
    static_assert(is_std_integral_constant_size_or_std_size_v<CAPACITY_TYPE>);

   public:
    using capacity_type = CAPACITY_TYPE;
    using element_type  = T;

   protected:
    T* _data;
    capacity_type _capacity;

   public:
    constexpr View_Default_Memory_Chunk(T* data, capacity_type capacity)
        : _data(data), _capacity(capacity)
    {
    }

    constexpr capacity_type
    capacity() const
    {
      return _capacity;
    }

    constexpr element_type*
    data()
    {
      return _data;
    }
    constexpr const element_type*
    data() const
    {
      return _data;
    }
  };

  //----------------------------------------------------------------

  // Note: for views as we store the same raw pointer type for dynamic
  // & static cases, not need for specialization
  //
  template <typename T, typename CAPACITY_TYPE>
  class Const_View_Default_Memory_Chunk
  {
    static_assert(is_std_integral_constant_size_or_std_size_v<CAPACITY_TYPE>);

   public:
    using capacity_type = CAPACITY_TYPE;
    using element_type  = T;

   protected:
    const T* _data;
    capacity_type _capacity;

   public:
    constexpr Const_View_Default_Memory_Chunk(const T* data, capacity_type capacity)
        : _data(data), _capacity(capacity)
    {
    }

    constexpr capacity_type
    capacity() const
    {
      return _capacity;
    }

    constexpr element_type*
    data()
    {
      return _data;
    }
    constexpr const element_type*
    data() const
    {
      return _data;
    }
  };

  // //****************************************************************
  // // TODO: must be replaced by Default_Memory_Chunk
  // //
  // template <typename T, std::size_t N>
  // class Tiny_Memory_Chunk
  // {
  //  public:
  //   using capacity_type = std::integral_constant<std::size_t, N>;
  //   using element_type  = T;

  //  protected:
  //   std::array<T, N> _data;

  //  public:
  //   capacity_type capacity() const { return {}; }

  //   element_type*       data() { return _data.data(); }
  //   const element_type* data() const { return _data.data(); }
  // };

  // //****************************************************************

  // template <typename T, std::size_t N>
  // class Tiny_Memory_Chunk_View
  // {
  //  public:
  //   using capacity_type = std::integral_constant<std::size_t, N>;
  //   using element_type  = T;

  //  protected:
  //   T* _data;

  //  public:
  //   Tiny_Memory_Chunk_View(T* data) : _data(data) {}  // (T* data,size) <- TODO

  //   capacity_type capacity() const { return {}; }

  //   // Note: method with "const" qualifier, also see
  //   // Tiny_Memory_Chunk_Const_View
  //   element_type* data() const { return _data; }
  // };

  // //================================================================

  // template <typename T, std::size_t N>
  // class Tiny_Memory_Chunk_Const_View
  // {
  //  public:
  //   using capacity_type = std::integral_constant<std::size_t, N>;
  //   using element_type  = T;

  //  protected:
  //   const T* _data;

  //  public:
  //   Tiny_Memory_Chunk_Const_View(const T* data) : _data(data) {}  // (const T* data,size) <- TODO

  //   capacity_type capacity() const { return {}; }

  //   const element_type* data() const { return _data; }
  // };

}
