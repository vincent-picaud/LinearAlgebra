#pragma once

#include "LinearAlgebra/dense/memory_chunk.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/vector_storage_scheme.hpp"

namespace LinearAlgebra
{
  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector;

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Vector<T, SIZE_TYPE, INCREMENT_TYPE>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Vector_Storage_Scheme<SIZE_TYPE, INCREMENT_TYPE>;
    using memory_chunk_type =
        LinearAlgebra::Default_Memory_Chunk<T,
                                            typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using size_type = typename storage_scheme_type::size_type;  // vector dimension

    using increment_type = typename storage_scheme_type::increment_type;
  };

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector : public Dense_Vector_Crtp<Default_Vector<T, SIZE_TYPE, INCREMENT_TYPE>>
  {
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<SIZE_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT_TYPE>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Vector_Crtp<Default_Vector<T, SIZE_TYPE, INCREMENT_TYPE>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using size_type = typename base_type::size_type;

    using increment_type = typename base_type::increment_type;

    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    Default_Vector() : base_type(storage_scheme_type()) {}
    Default_Vector(const SIZE_TYPE n, const INCREMENT_TYPE inc)
        : base_type(storage_scheme_type(n, inc))
    {
    }
    // Note: explicit blocks to possible wrong interpreation of V=3
    //       which would be the construction of a vector of size 3.
    explicit Default_Vector(const SIZE_TYPE n) : base_type(storage_scheme_type(n)) {}

    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
    // Meta expression
    template <typename METAEXPR_IMPL>
    Default_Vector&
    operator=(const Detail::MetaExpr_Crtp<METAEXPR_IMPL>& metaExpr)
    {
      return this->impl_assign(metaExpr);
    }

    Default_Vector&
    operator=(const element_type& scalar)
    {
      return this->impl_assign(scalar);
    }
  };

  //****************************************************************
  // Views
  //
  // Very few changes ( tagged by "CHANGE HERE" )
  //
  // - uses View_Default_Memory_Chunk instead of Default_Memory_Chunk
  //
  // - modifies Default_Vector to take a pointer (to feed
  //   View_Default_Memory_Chunk)
  //
  //****************************************************************

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector_View;

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Vector_View<T, SIZE_TYPE, INCREMENT_TYPE>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Vector_Storage_Scheme<SIZE_TYPE,
                                                     INCREMENT_TYPE>;  // <- "CHANGE HERE"
    using memory_chunk_type = LinearAlgebra::View_Default_Memory_Chunk<
        T, typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using size_type = typename storage_scheme_type::size_type;  // vector dimension

    using increment_type = typename storage_scheme_type::increment_type;
  };

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector_View
      : public Dense_Vector_Crtp<Default_Vector_View<T, SIZE_TYPE, INCREMENT_TYPE>>
  {
    // Sanity checks
    //
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<SIZE_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT_TYPE>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Vector_Crtp<Default_Vector_View<T, SIZE_TYPE, INCREMENT_TYPE>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using size_type = typename base_type::size_type;

    using increment_type = typename base_type::increment_type;

    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    Default_Vector_View(T* data) : base_type(storage_scheme_type(), data) {}   // <- "CHANGE HERE"
    Default_Vector_View(T* data, const SIZE_TYPE n, const INCREMENT_TYPE inc)  // <- "CHANGE HERE"
        : base_type(storage_scheme_type(n, inc), data)
    {
    }

    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
    // Meta expression
    template <typename METAEXPR_IMPL>
    Default_Vector_View&
    operator=(const Detail::MetaExpr_Crtp<METAEXPR_IMPL>& metaExpr)
    {
      return this->impl_assign(metaExpr);
    }

    Default_Vector_View&
    operator=(const element_type& scalar)
    {
      return this->impl_assign(scalar);
    }
  };

  //****************************************************************
  // Const_View
  //****************************************************************

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector_Const_View;

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Vector_Const_View<T, SIZE_TYPE, INCREMENT_TYPE>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Vector_Storage_Scheme<SIZE_TYPE, INCREMENT_TYPE>;
    using memory_chunk_type = LinearAlgebra::Const_View_Default_Memory_Chunk<
        T, typename storage_scheme_type::
               required_capacity_type>;  // <- "CHANGE HERE" View -> Const_View

    using element_type = typename memory_chunk_type::element_type;

    using size_type = typename storage_scheme_type::size_type;

    using increment_type = typename storage_scheme_type::increment_type;
  };

  template <typename T, typename SIZE_TYPE, typename INCREMENT_TYPE>
  class Default_Vector_Const_View
      : public Dense_Vector_Crtp<Default_Vector_Const_View<T, SIZE_TYPE, INCREMENT_TYPE>>
  {
    // Sanity checks
    //
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<SIZE_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT_TYPE>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Vector_Crtp<Default_Vector_Const_View<T, SIZE_TYPE, INCREMENT_TYPE>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using size_type = typename base_type::size_type;

    using increment_type = typename base_type::increment_type;

    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    Default_Vector_Const_View(const T* data)
        : base_type(storage_scheme_type(), data) {}  // <- "CHANGE HERE" T* -> const T*
    Default_Vector_Const_View(const T* data, const SIZE_TYPE n,
                              const INCREMENT_TYPE inc)  // <- "CHANGE HERE" T* -> const T*
        : base_type(storage_scheme_type(n, inc), data)
    {
    }
    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
    // Meta expression
    template <typename METAEXPR_IMPL>
    Default_Vector_Const_View&
    operator=(const Detail::MetaExpr_Crtp<METAEXPR_IMPL>& metaExpr)
    {
      return this->impl_assign(metaExpr);
    }

    Default_Vector_Const_View&
    operator=(const element_type& scalar)
    {
      return this->impl_assign(scalar);
    }
  };

  ////////////////
  // Some Alias //
  ////////////////

  template <typename T, size_t SIZE>
  using Tiny_Vector = Default_Vector<T, std::integral_constant<std::size_t, SIZE>,
                                     std::integral_constant<std::size_t, 1>>;

  template <typename T>
  using Vector = Default_Vector<T, size_t, std::integral_constant<std::size_t, 1>>;

}
