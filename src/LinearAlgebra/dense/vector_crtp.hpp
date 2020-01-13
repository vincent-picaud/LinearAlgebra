#pragma once

#include <cstddef>

#include "KissCore/crtp.hpp"

namespace KissDStream
{
  template <typename IMPL = KissCore::Crtp_Final_Impl>
  class Vector_Crtp : public KissCore::Crtp_Find_Impl<Vector_Crtp, IMPL, KissCore::Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = KissCore::Crtp_Find_Impl<Vector_Crtp, IMPL, KissCore::Crtp>;
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
  template <typename IMPL = KissCore::Crtp_Final_Impl>
  class Default_Vector_Crtp
      : public KissCore::Crtp_Find_Impl<Default_Vector_Crtp, IMPL, Vector_Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = KissCore::Crtp_Find_Impl<Default_Vector_Crtp, IMPL, Vector_Crtp>;

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
    Default_Vector_Crtp(const storage_scheme_type& storage_scheme)
        : _storage_scheme(storage_scheme), _memory_chunk(_storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }
    // This constructor assumes a view
    Default_Vector_Crtp(const storage_scheme_type& storage_scheme, element_type* p)
        : _storage_scheme(storage_scheme), _memory_chunk(p, _storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }
    // This constructor assumes a const view
    Default_Vector_Crtp(const storage_scheme_type& storage_scheme, const element_type* p)
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

    // Note: pass by reference (allows to use noncopyable lambda)
    template <typename LAMBDA>
    void
    map(const LAMBDA& lambda) const
    {
      base_type::impl().impl_map(lambda);
    }
    template <typename LAMBDA>
    void
    map(const LAMBDA& lambda)
    {
      base_type::impl().impl_map(lambda);
    }

    template <typename LAMBDA>
    void
    map_indexed(const LAMBDA& lambda) const
    {
      base_type::impl().impl_map_indexed(lambda);
    }
    template <typename LAMBDA>
    void
    map_indexed(const LAMBDA& lambda)
    {
      base_type::impl().impl_map_indexed(lambda);
    }

    const storage_scheme_type&
    storage_scheme() const
    {
      return base_type::impl().impl_storage_scheme();
    };

    /////////////////////////
    // Crtp Implementation //
    /////////////////////////
    //
   protected:
    friend base_type;
    friend typename base_type::base_type;

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

    template <typename LAMBDA>
    void
    impl_map(const LAMBDA& lambda) const
    {
      _storage_scheme.loop_over_indices([&lambda, this](const size_t i) { lambda((*this)[i]); });
    }
    template <typename LAMBDA>
    void
    impl_map(const LAMBDA& lambda)
    {
      _storage_scheme.loop_over_indices([&lambda, this](const size_t i) { lambda((*this)[i]); });
    }

    template <typename LAMBDA>
    void
    impl_map_indexed(const LAMBDA& lambda) const
    {
      _storage_scheme.loop_over_indices([&lambda, this](const size_t i) { lambda((*this)[i], i); });
    }
    template <typename LAMBDA>
    void
    impl_map_indexed(const LAMBDA& lambda)
    {
      _storage_scheme.loop_over_indices([&lambda, this](const size_t i) { lambda((*this)[i], i); });
    }
  };

  template <typename IMPL>
  void
  iota(Default_Vector_Crtp<IMPL>& to_fill, typename Default_Vector_Crtp<IMPL>::element_type start)
  {
    to_fill.map([&start](auto& v_i) {
      v_i = start;
      start += 1;
    });
  }

  template <typename IMPL>
  std::ostream&
  operator<<(std::ostream& out, const Default_Vector_Crtp<IMPL>& to_print)
  {
    const auto n = to_print.size();

    for (size_t i = 0; i < n; ++i)
    {
      out << "\n" << to_print[i];
    }
    return out;
  }

}
