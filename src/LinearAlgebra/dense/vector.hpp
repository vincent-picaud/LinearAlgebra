#pragma once

#include "LinearAlgebra/dense/memory_chunk.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/dense/vector_storage_scheme.hpp"

namespace LinearAlgebra
{
  template <typename T, typename N_TYPE, typename INCREMENT>
  class Default_Vector;

  template <typename T, typename N_TYPE, typename INCREMENT>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Vector<T, N_TYPE, INCREMENT>>
  {
    using storage_scheme_type = LinearAlgebra::Default_Vector_Storage_Scheme<N_TYPE, INCREMENT>;
    using memory_chunk_type =
        LinearAlgebra::Default_Memory_Chunk<T,
                                            typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using size_type = typename storage_scheme_type::size_type;  // vector dimension

    using increment_type = typename storage_scheme_type::increment_type;
  };

  template <typename T, typename N_TYPE, typename INCREMENT>
  class Default_Vector : public Default_Vector_Crtp<Default_Vector<T, N_TYPE, INCREMENT>>
  {
    // Sanity checks
    //
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<N_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Default_Vector_Crtp<Default_Vector<T, N_TYPE, INCREMENT>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using size_type = typename base_type::size_type;

    using increment_type = typename base_type::increment_type;

    /////////////
    // Members //
    /////////////
    //
   protected:
    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    Default_Vector() : base_type(storage_scheme_type()) {}
    Default_Vector(const N_TYPE n, const INCREMENT inc) : base_type(storage_scheme_type(n, inc)) {}
    Default_Vector(const N_TYPE n) : base_type(storage_scheme_type(n)) {}
    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
  };

  //================

  template <typename T, size_t N>
  using Tiny_Vector = Default_Vector<T, std::integral_constant<std::size_t, N>,
                                     std::integral_constant<std::size_t, 1>>;

  template <typename T>
  using Vector = Default_Vector<T, size_t, std::integral_constant<std::size_t, 1>>;

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

  template <typename T, typename N_TYPE, typename INCREMENT>
  class Default_Vector_View;

  template <typename T, typename N_TYPE, typename INCREMENT>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Vector_View<T, N_TYPE, INCREMENT>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Vector_Storage_Scheme<N_TYPE,
                                                     INCREMENT>;  // <- "CHANGE HERE"
    using memory_chunk_type = LinearAlgebra::View_Default_Memory_Chunk<
        T, typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using size_type = typename storage_scheme_type::size_type;  // vector dimension

    using increment_type = typename storage_scheme_type::increment_type;
  };
}

namespace LinearAlgebra
{
  template <typename T, typename N_TYPE, typename INCREMENT>
  class Default_Vector_View : public Default_Vector_Crtp<Default_Vector_View<T, N_TYPE, INCREMENT>>
  {
    // Sanity checks
    //
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<N_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Default_Vector_Crtp<Default_Vector_View<T, N_TYPE, INCREMENT>>;

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
    Default_Vector_View(T* data) : base_type(storage_scheme_type(), data) {}  // <- "CHANGE HERE"
    Default_Vector_View(T* data, const N_TYPE n, const INCREMENT inc)         // <- "CHANGE HERE"
        : base_type(storage_scheme_type(n, inc), data)
    {
    }
  };

  //================

  template <typename T, size_t N>
  using Tiny_Vector_View = Default_Vector_View<T, std::integral_constant<std::size_t, N>,
                                               std::integral_constant<std::size_t, 1>>;

  template <typename T>
  using Vector_View = Default_Vector_View<T, size_t, std::integral_constant<std::size_t, 1>>;

  //****************************************************************
  // Const_View
  //****************************************************************

  template <typename T, typename N_TYPE, typename INCREMENT>
  class Default_Vector_Const_View;

  template <typename T, typename N_TYPE, typename INCREMENT>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Vector_Const_View<T, N_TYPE, INCREMENT>>
  {
    using storage_scheme_type = LinearAlgebra::Default_Vector_Storage_Scheme<N_TYPE, INCREMENT>;
    using memory_chunk_type   = LinearAlgebra::Const_View_Default_Memory_Chunk<
        T, typename storage_scheme_type::
               required_capacity_type>;  // <- "CHANGE HERE" View -> Const_View

    using element_type = typename memory_chunk_type::element_type;

    using size_type = typename storage_scheme_type::size_type;

    using increment_type = typename storage_scheme_type::increment_type;
  };

  template <typename T, typename N_TYPE, typename INCREMENT>
  class Default_Vector_Const_View
      : public Default_Vector_Crtp<Default_Vector_Const_View<T, N_TYPE, INCREMENT>>
  {
    // Sanity checks
    //
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<N_TYPE>);
    static_assert(Is_Std_Integral_Constant_Size_Or_Std_Size_v<INCREMENT>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Default_Vector_Crtp<Default_Vector_Const_View<T, N_TYPE, INCREMENT>>;

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
    Default_Vector_Const_View(const T* data, const N_TYPE n,
                              const INCREMENT inc)  // <- "CHANGE HERE" T* -> const T*
        : base_type(storage_scheme_type(n, inc), data)
    {
    }
  };

  //================

  template <typename T, size_t N>
  using Tiny_Vector_Const_View =
      Default_Vector_Const_View<T, std::integral_constant<std::size_t, N>,
                                std::integral_constant<std::size_t, 1>>;

  template <typename T>
  using Vector_Const_View =
      Default_Vector_Const_View<T, size_t, std::integral_constant<std::size_t, 1>>;
}
