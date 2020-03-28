#pragma once

#include <cstddef>

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha.hpp"
#include "LinearAlgebra/expr/V0_assign_V1.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp_fwd.hpp"

namespace LinearAlgebra
{
  template <typename IMPL>
  class Vector_Crtp : public Crtp_Find_Impl<Vector_Crtp, IMPL, Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Crtp_Find_Impl<Vector_Crtp, IMPL, Crtp>;
    using base_type::impl;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;
    using size_type    = typename traits_type::size_type;

    ////////////////////
    // Crtp Interface //
    ////////////////////
    //
   public:
    size_type
    size() const
    {
      return base_type::impl().impl_size();
    }

    const IMPL&
    as_const() const
    {
      return base_type::impl();
    }

    /////////////////////////
    // Crpt Implementation //
    /////////////////////////
    //
   protected:
  };

  //****************************************************************

  // By "default" we assume that we use the storage_scheme,
  // memory_chunk policies
  template <typename IMPL>
  class Dense_Vector_Crtp : public Crtp_Find_Impl<Dense_Vector_Crtp, IMPL, Vector_Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Crtp_Find_Impl<Dense_Vector_Crtp, IMPL, Vector_Crtp>;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    // Note: take habit to put storage first, as it can be used to
    // compute required_capacity needed by memory_chunk
    using storage_scheme_type = typename traits_type::storage_scheme_type;
    using memory_chunk_type   = typename traits_type::memory_chunk_type;
    using increment_type      = typename traits_type::increment_type;
    static_assert(std::is_same_v<typename storage_scheme_type::increment_type, increment_type>);
    using element_type = typename traits_type::element_type;
    static_assert(std::is_same_v<typename memory_chunk_type::element_type, element_type>);

    using size_type = typename base_type::size_type;
    static_assert(std::is_same_v<typename storage_scheme_type::size_type, size_type>);

    /////////////
    // Members //
    /////////////
    //
   protected:
    storage_scheme_type _storage_scheme;
    memory_chunk_type _memory_chunk;

    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    // Default_Vector_Crtp(storage_scheme_type&& storage_scheme,
    //                             memory_chunk_type&&   memory_chunk)
    //     : _storage_scheme(std::move(storage_scheme)), _memory_chunk(std::move(memory_chunk))
    // {
    //   assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    // }

    // This constructor assumes than memory_chunk allocates its memory
    Dense_Vector_Crtp(const storage_scheme_type& storage_scheme)
        : _storage_scheme(storage_scheme), _memory_chunk(_storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }
    // This constructor assumes a view
    Dense_Vector_Crtp(const storage_scheme_type& storage_scheme, element_type* p)
        : _storage_scheme(storage_scheme), _memory_chunk(p, _storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }
    // This constructor assumes a const view
    Dense_Vector_Crtp(const storage_scheme_type& storage_scheme, const element_type* p)
        : _storage_scheme(storage_scheme), _memory_chunk(p, _storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }

   public:
    ////////////////////
    // Crtp Interface //
    ////////////////////
    //

    // auto makes sense for const views
    auto*
    data()
    {
      return base_type::impl().impl_data();
    }
    const element_type*
    data() const
    {
      return base_type::impl().impl_data();
    }

    increment_type
    increment() const
    {
      return base_type::impl().impl_increment();
    }

    // Note: for mutable version it's important to use auto, as
    // memory_chunk.data() maybe returns "const element_type*".  This
    // is the case for Const_View for instance.
    auto& operator[](const size_t idx) { return base_type::impl().impl_random_access(idx); }
    const element_type& operator[](const size_t idx) const
    {
      return base_type::impl().impl_random_access(idx);
    }

    const storage_scheme_type&
    storage_scheme() const
    {
      return base_type::impl().impl_storage_scheme();
    };

    const memory_chunk_type&
    memory_chunk() const
    {
      return base_type::impl().impl_memory_chunk();
    };


    /////////////////////////
    // Crtp Implementation //
    /////////////////////////
    //
   protected:
    friend base_type;
    friend typename base_type::base_type;

    template <typename METAEXPR_IMPL>
    IMPL&
    impl_assign(const Detail::MetaExpr_Crtp<METAEXPR_IMPL>& metaExpr)
    {
      call_assign_from_metaexpr(*this, metaExpr);
      return base_type::impl();
    }

    IMPL&
    impl_assign(const element_type& scalar)
    {
      assign(*this, scalar);
      return base_type::impl();
    }
    
    template <typename OTHER_IMPL>
    IMPL&
    impl_assign(const Vector_Crtp<OTHER_IMPL>& other_vector)
    {
      assign(*this, other_vector);
      return base_type::impl();
    }

    size_type
    impl_size() const
    {
      return _storage_scheme.size();
    }

    auto*
    impl_data()
    {
      return _memory_chunk.data();
    };
    const element_type*
    impl_data() const
    {
      return _memory_chunk.data();
    };

    increment_type
    impl_increment() const
    {
      return _storage_scheme.increment();
    }
    const storage_scheme_type&
    impl_storage_scheme() const
    {
      return _storage_scheme;
    }
    const memory_chunk_type&
    impl_memory_chunk() const
    {
      return _memory_chunk;
    }

    auto&
    impl_random_access(const size_t idx)
    {
      assert(_storage_scheme.check_index(idx));
      return *(_memory_chunk.data() + _storage_scheme.offset(idx));
    }
    const element_type&
    impl_random_access(const size_t idx) const
    {
      assert(_storage_scheme.check_index(idx));
      return *(_memory_chunk.data() + _storage_scheme.offset(idx));
    }
  };

  // TODO to move elsewhere and use transform
  template <typename IMPL>
  void
  iota(Dense_Vector_Crtp<IMPL>& to_fill, typename Dense_Vector_Crtp<IMPL>::element_type start)
  {
    const auto n = to_fill.size();
    for (size_t i = 0; i < n; ++i)
    {
      to_fill[i] = start + i;
    };
  }

  template <typename IMPL>
  std::ostream&
  operator<<(std::ostream& out, const Dense_Vector_Crtp<IMPL>& to_print)
  {
    const auto n = to_print.size();

    for (size_t i = 0; i < n; ++i)
    {
      out << "\n" << to_print[i];
    }
    return out;
  }

}
