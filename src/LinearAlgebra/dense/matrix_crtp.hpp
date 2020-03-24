#pragma once

#include <cstddef>
#include <iomanip>

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"

namespace LinearAlgebra
{
  template <typename IMPL>
  class Matrix_Crtp : public Crtp_Find_Impl<Matrix_Crtp, IMPL, Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Crtp_Find_Impl<Matrix_Crtp, IMPL, Crtp>;
    using base_type::impl;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    using element_type = typename traits_type::element_type;
    using I_size_type  = typename traits_type::I_size_type;
    using J_size_type  = typename traits_type::J_size_type;

    ////////////////////
    // Crtp Interface //
    ////////////////////
    //
   public:
    I_size_type
    I_size() const
    {
      return base_type::impl().impl_I_size();
    }
    J_size_type
    J_size() const
    {
      return base_type::impl().impl_J_size();
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

  template <typename IMPL>
  class Dense_Matrix_Crtp : public Crtp_Find_Impl<Dense_Matrix_Crtp, IMPL, Matrix_Crtp>
  {
    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Crtp_Find_Impl<Dense_Matrix_Crtp, IMPL, Matrix_Crtp>;

    using exact_type  = typename base_type::exact_type;
    using traits_type = typename base_type::traits_type;

    // Note: take habit to put storage first, as it can be used to
    // compute required_capacity
    using storage_scheme_type    = typename traits_type::storage_scheme_type;
    using memory_chunk_type      = typename traits_type::memory_chunk_type;
    using leading_dimension_type = typename traits_type::leading_dimension_type;
    static_assert(std::is_same_v<typename storage_scheme_type::leading_dimension_type,
                                 leading_dimension_type>);

    using matrix_special_structure_type = typename traits_type::matrix_special_structure_type;

    using matrix_storage_mask_type = typename storage_scheme_type::matrix_storage_mask_type;

    using element_type = typename traits_type::element_type;
    static_assert(std::is_same_v<typename memory_chunk_type::element_type, element_type>);

    using I_size_type = typename base_type::I_size_type;
    static_assert(std::is_same_v<typename storage_scheme_type::I_size_type, I_size_type>);
    using J_size_type = typename base_type::J_size_type;
    static_assert(std::is_same_v<typename storage_scheme_type::J_size_type, J_size_type>);

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
    // This constructor assumes than memory_chunk allocates its memory
    Dense_Matrix_Crtp(const storage_scheme_type& storage_scheme)
        : _storage_scheme(storage_scheme), _memory_chunk(_storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }
    // This constructor assumes a view
    Dense_Matrix_Crtp(const storage_scheme_type& storage_scheme, element_type* p)
        : _storage_scheme(storage_scheme), _memory_chunk(p, _storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }
    // This constructor assumes a const view
    Dense_Matrix_Crtp(const storage_scheme_type& storage_scheme, const element_type* p)
        : _storage_scheme(storage_scheme), _memory_chunk(p, _storage_scheme.required_capacity())
    {
      assert(_storage_scheme.required_capacity() <= _memory_chunk.capacity());
    }

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

    leading_dimension_type
    leading_dimension() const
    {
      return base_type::impl().impl_leading_dimension();
    }

    // Note: for mutable version important to use auto, as
    // memory_chunk.data() maybe returns "const element_type*".
    // This is the case for Const_View for instance.
    auto&
    operator()(const size_t i, const size_t j)
    {
      return base_type::impl().impl_random_access(i, j);
    }
    const element_type&
    operator()(const size_t i, const size_t j) const
    {
      return base_type::impl().impl_random_access(i, j);
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

   public:
    /////////////////////////
    // Crtp Implementation //
    /////////////////////////
    //
   protected:
    friend base_type;
    friend typename base_type::base_type;

    I_size_type
    impl_I_size() const
    {
      return _storage_scheme.I_size();
    }
    J_size_type
    impl_J_size() const
    {
      return _storage_scheme.J_size();
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

    leading_dimension_type
    impl_leading_dimension() const
    {
      return _storage_scheme.leading_dimension();
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
    impl_random_access(const size_t i, const size_t j)
    {
      assert(_storage_scheme.check_index(i, j));
      return *(data() + _storage_scheme.offset(i, j));
    }
    const element_type&
    impl_random_access(const size_t i, const size_t j) const
    {
      assert(_storage_scheme.check_index(i, j));
      return *(data() + _storage_scheme.offset(i, j));
    }
  };

  template <typename IMPL>
  std::ostream&
  operator<<(std::ostream& out, const Dense_Matrix_Crtp<IMPL>& to_print)
  {
    const auto& storage_scheme = to_print.storage_scheme();

    const auto n = to_print.I_size();
    const auto m = to_print.J_size();

    for (size_t i = 0; i < n; ++i)
    {
      out << "\n";
      for (size_t j = 0; j < m; ++j)
      {
        out << std::setw(16);
        if (storage_scheme.check_index(i, j))
        {
          out << to_print(i, j);
        }
        else
        {
          out << "X";
        }
      }
    }
    return out;
  }
}
