// TODO: for hermitian matrices, check that diagonal is real
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"
#include "LinearAlgebra/dense/memory_chunk.hpp"
#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

// Detail
#include "LinearAlgebra/dense/dynamic_to_static_helper.hpp"
#include "LinearAlgebra/dense/vmt_assignment_operator_define.hpp"

// Allowed combination Structure + Mask
//
namespace LinearAlgebra
{
  namespace Default_Matrix_Detail
  {
    template <Matrix_Special_Structure_Enum SPECIAL_STRUCTURE, Matrix_Storage_Mask_Enum MASK>
    struct Is_Structure_Mask_Combination_Allowed : std::false_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::None,
                                                 Matrix_Storage_Mask_Enum::None> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Symmetric,
                                                 Matrix_Storage_Mask_Enum::Lower> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Symmetric,
                                                 Matrix_Storage_Mask_Enum::Upper> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Hermitian,
                                                 Matrix_Storage_Mask_Enum::Lower> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Hermitian,
                                                 Matrix_Storage_Mask_Enum::Upper> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Triangular,
                                                 Matrix_Storage_Mask_Enum::Lower> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Triangular,
                                                 Matrix_Storage_Mask_Enum::Upper> : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Unit_Triangular,
                                                 Matrix_Storage_Mask_Enum::Lower_Strict>
        : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Unit_Triangular,
                                                 Matrix_Storage_Mask_Enum::Upper_Strict>
        : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Triangular_Strict,
                                                 Matrix_Storage_Mask_Enum::Lower_Strict>
        : std::true_type
    {
    };

    template <>
    struct Is_Structure_Mask_Combination_Allowed<Matrix_Special_Structure_Enum::Triangular_Strict,
                                                 Matrix_Storage_Mask_Enum::Upper_Strict>
        : std::true_type
    {
    };

    template <Matrix_Special_Structure_Enum SPECIAL_STRUCTURE, Matrix_Storage_Mask_Enum MASK>
    constexpr bool is_structure_mask_combination_allowed_v =
        Is_Structure_Mask_Combination_Allowed<SPECIAL_STRUCTURE, MASK>::value;

    template <typename T,
              Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK,
              typename I_SIZE_TYPE,
              typename J_SIZE_TYPE,
              typename LEADING_DIMENSION_TYPE>
    constexpr bool sanity_check_v =
        is_structure_mask_combination_allowed_v<SPECIAL_STRUCTURE, MASK>and
            Is_Std_Integral_Constant_Size_Or_Std_Size_v<I_SIZE_TYPE>and
                Is_Std_Integral_Constant_Size_Or_Std_Size_v<J_SIZE_TYPE>and
                    Is_Std_Integral_Constant_Size_Or_Std_Size_v<LEADING_DIMENSION_TYPE>;

  }  // namespace Default_Matrix_Detail

  // Below concrete implementations Default_Matrix_Crtp<> of are defined:
  //
  // - Default_Matrix
  // - Default_Matrix_View
  // - Default_Matrix_Const_View
  //

  template <typename T,
            LinearAlgebra::Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            LinearAlgebra::Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Matrix<T,
                                                        SPECIAL_STRUCTURE,
                                                        MASK,
                                                        I_SIZE_TYPE,
                                                        J_SIZE_TYPE,
                                                        LEADING_DIMENSION_TYPE>>
  {
    using storage_scheme_type = LinearAlgebra::
        Default_Matrix_Storage_Scheme<MASK, I_SIZE_TYPE, J_SIZE_TYPE, LEADING_DIMENSION_TYPE>;
    using memory_chunk_type =
        LinearAlgebra::Default_Memory_Chunk<T,
                                            typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

    using matrix_special_structure_type =
        std::integral_constant<LinearAlgebra::Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>;
  };

  template <typename T,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  class Default_Matrix : public Dense_Matrix_Crtp<Default_Matrix<T,
                                                                 SPECIAL_STRUCTURE,
                                                                 MASK,
                                                                 I_SIZE_TYPE,
                                                                 J_SIZE_TYPE,
                                                                 LEADING_DIMENSION_TYPE>>
  {
    static_assert(Default_Matrix_Detail::sanity_check_v<T,
                                                        SPECIAL_STRUCTURE,
                                                        MASK,
                                                        I_SIZE_TYPE,
                                                        J_SIZE_TYPE,
                                                        LEADING_DIMENSION_TYPE>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Matrix_Crtp<Default_Matrix<T,
                                                       SPECIAL_STRUCTURE,
                                                       MASK,
                                                       I_SIZE_TYPE,
                                                       J_SIZE_TYPE,
                                                       LEADING_DIMENSION_TYPE>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using I_size_type = typename base_type::I_size_type;
    using J_size_type = typename base_type::J_size_type;

    using leading_dimension_type = typename base_type::leading_dimension_type;

    // note: these static enum values
    //   - matrix_special_structure_type     : Triangular, Symmetric...
    //   - matrix_storage_mask_type          : Upper, None...
    // can be accessed and are defined in the inherited Default_Matrix_Crtp class
    //

    /////////////
    // Members: nothing!
    /////////////
    //
   protected:
    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    Default_Matrix() : base_type(storage_scheme_type()) {}

    // Note: this tells to reuse the constructors define in
    //       Default_Matrix_Crtp
    Default_Matrix(const Default_Matrix&) = default;
    Default_Matrix(Default_Matrix&&)      = default;

    // Extend copy constructor using other matrix type as source
    template <typename OTHER_IMPL>
    Default_Matrix(const Matrix_Crtp<OTHER_IMPL>& other)
        : Default_Matrix(Detail::Dynamic_To_Static_Helper<I_SIZE_TYPE>(other.I_size()),
                         Detail::Dynamic_To_Static_Helper<J_SIZE_TYPE>(other.J_size()))
    {
      (*this) = other;
    }

    // Default_Matrix(const I_SIZE_TYPE n, const J_SIZE_TYPE m, const LEADING_DIMENSION_TYPE ld)
    //     : base_type(storage_scheme_type(n, m, ld))
    // {
    //   assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
    //          (base_type::I_size() == base_type::J_size()));
    // }
    // Default_Matrix(const I_SIZE_TYPE n, const J_SIZE_TYPE m) : base_type(storage_scheme_type(n, m))
    // {
    //   assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
    //          (base_type::I_size() == base_type::J_size()));
    // }

    Default_Matrix(const Detail::Dynamic_To_Static_Helper<I_SIZE_TYPE> n,
                   const Detail::Dynamic_To_Static_Helper<J_SIZE_TYPE> m,
                   const Detail::Dynamic_To_Static_Helper<LEADING_DIMENSION_TYPE> ld)
        : base_type(storage_scheme_type(n, m, ld))
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }

    Default_Matrix(const Detail::Dynamic_To_Static_Helper<I_SIZE_TYPE> n,
                   const Detail::Dynamic_To_Static_Helper<J_SIZE_TYPE> m)
        : base_type(storage_scheme_type(n, m))
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }

    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
    // Generic View Converter
    operator Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>() const
    {
      return impl_as_generic_view();
    }
    operator Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>()
    {
      return this->as_const().impl_as_generic_view();
    }
    operator Generic_Matrix_View<T, SPECIAL_STRUCTURE, MASK>() { return impl_as_generic_view(); }

    VMT_ASSIGNMENT_OPERATOR(Default_Matrix);

    ///////////////////////////////////
    // Crtp Interface Implementation //
    ///////////////////////////////////
    //
   protected:
    friend base_type;

    Generic_Matrix_View<T, SPECIAL_STRUCTURE, MASK>
    impl_as_generic_view()
    {
      return {this->data(), this->I_size(), this->J_size(), this->leading_dimension()};
    }
    Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>
    impl_as_generic_view() const
    {
      return {this->data(), this->I_size(), this->J_size(), this->leading_dimension()};
    }
  };

  //****************************************************************

  template <typename T,
            LinearAlgebra::Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            LinearAlgebra::Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Matrix_View<T,
                                                             SPECIAL_STRUCTURE,
                                                             MASK,
                                                             I_SIZE_TYPE,
                                                             J_SIZE_TYPE,
                                                             LEADING_DIMENSION_TYPE>>
  {
    using storage_scheme_type = LinearAlgebra::
        Default_Matrix_Storage_Scheme<MASK, I_SIZE_TYPE, J_SIZE_TYPE, LEADING_DIMENSION_TYPE>;
    using memory_chunk_type = LinearAlgebra::
        View_Default_Memory_Chunk<T, typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

    using matrix_special_structure_type =
        std::integral_constant<LinearAlgebra::Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>;
  };

  template <typename T,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  class Default_Matrix_View : public Dense_Matrix_Crtp<Default_Matrix_View<T,
                                                                           SPECIAL_STRUCTURE,
                                                                           MASK,
                                                                           I_SIZE_TYPE,
                                                                           J_SIZE_TYPE,
                                                                           LEADING_DIMENSION_TYPE>>
  {
    static_assert(Default_Matrix_Detail::sanity_check_v<T,
                                                        SPECIAL_STRUCTURE,
                                                        MASK,
                                                        I_SIZE_TYPE,
                                                        J_SIZE_TYPE,
                                                        LEADING_DIMENSION_TYPE>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Matrix_Crtp<Default_Matrix_View<T,
                                                            SPECIAL_STRUCTURE,
                                                            MASK,
                                                            I_SIZE_TYPE,
                                                            J_SIZE_TYPE,
                                                            LEADING_DIMENSION_TYPE>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

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
    Default_Matrix_View() : Default_Matrix_View(nullptr) { assert(this->data() == nullptr); }

    Default_Matrix_View(T* data) : base_type(storage_scheme_type(), data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }
    Default_Matrix_View(T* data,
                        const I_SIZE_TYPE n,
                        const J_SIZE_TYPE m,
                        const LEADING_DIMENSION_TYPE ld)
        : base_type(storage_scheme_type(n, m, ld), data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }
    Default_Matrix_View(const storage_scheme_type& storage_scheme, T* data)
        : base_type(storage_scheme, data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }
    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
    // Generic View Converter
    operator Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>() const
    {
      return impl_as_generic_view();
    }
    operator Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>()
    {
      return this->as_const().impl_as_generic_view();
    }
    operator Generic_Matrix_View<T, SPECIAL_STRUCTURE, MASK>() { return impl_as_generic_view(); }

    VMT_ASSIGNMENT_OPERATOR(Default_Matrix_View);

    ///////////////////////////////////
    // Crtp Interface Implementation //
    ///////////////////////////////////
    //
   protected:
    friend base_type;

    Generic_Matrix_View<T, SPECIAL_STRUCTURE, MASK>
    impl_as_generic_view()
    {
      return {this->data(), this->I_size(), this->J_size(), this->leading_dimension()};
    }
    Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>
    impl_as_generic_view() const
    {
      return {this->data(), this->I_size(), this->J_size(), this->leading_dimension()};
    }
  };

  //================================================================

  template <typename T,
            LinearAlgebra::Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            LinearAlgebra::Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Matrix_Const_View<T,
                                                                   SPECIAL_STRUCTURE,
                                                                   MASK,
                                                                   I_SIZE_TYPE,
                                                                   J_SIZE_TYPE,
                                                                   LEADING_DIMENSION_TYPE>>
  {
    using storage_scheme_type = LinearAlgebra::
        Default_Matrix_Storage_Scheme<MASK, I_SIZE_TYPE, J_SIZE_TYPE, LEADING_DIMENSION_TYPE>;
    using memory_chunk_type = LinearAlgebra::
        Const_View_Default_Memory_Chunk<T, typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

    using matrix_special_structure_type =
        std::integral_constant<LinearAlgebra::Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>;
  };

  template <typename T,
            Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK,
            typename I_SIZE_TYPE,
            typename J_SIZE_TYPE,
            typename LEADING_DIMENSION_TYPE>
  class Default_Matrix_Const_View
      : public Dense_Matrix_Crtp<Default_Matrix_Const_View<T,
                                                           SPECIAL_STRUCTURE,
                                                           MASK,
                                                           I_SIZE_TYPE,
                                                           J_SIZE_TYPE,
                                                           LEADING_DIMENSION_TYPE>>
  {
    static_assert(Default_Matrix_Detail::sanity_check_v<T,
                                                        SPECIAL_STRUCTURE,
                                                        MASK,
                                                        I_SIZE_TYPE,
                                                        J_SIZE_TYPE,
                                                        LEADING_DIMENSION_TYPE>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Matrix_Crtp<Default_Matrix_Const_View<T,
                                                                  SPECIAL_STRUCTURE,
                                                                  MASK,
                                                                  I_SIZE_TYPE,
                                                                  J_SIZE_TYPE,
                                                                  LEADING_DIMENSION_TYPE>>;

    using storage_scheme_type = typename base_type::storage_scheme_type;
    using memory_chunk_type   = typename base_type::memory_chunk_type;

    using element_type = typename base_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

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
    Default_Matrix_Const_View() : Default_Matrix_Const_View(nullptr)
    {
      assert(this->data() == nullptr);
    }

    Default_Matrix_Const_View(const T* data) : base_type(storage_scheme_type(), data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }

    Default_Matrix_Const_View(const T* data,
                              const I_SIZE_TYPE n,
                              const J_SIZE_TYPE m,
                              const LEADING_DIMENSION_TYPE ld)
        : Default_Matrix_Const_View(storage_scheme_type(n, m, ld), data)
    {
    }

    Default_Matrix_Const_View(const storage_scheme_type& storage_scheme, const T* data)
        : base_type(storage_scheme, data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }

    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
    // Generic View Converter
    operator Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>() const
    {
      return impl_as_generic_view();
    }
    operator Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>()
    {
      return this->as_const().impl_as_generic_view();
    }

    DELETE_VMT_ASSIGNMENT_OPERATOR(Default_Matrix_Const_View);

    ///////////////////////////////////
    // Crtp Interface Implementation //
    ///////////////////////////////////
    //
   protected:
    friend base_type;

    Generic_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK>
    impl_as_generic_view() const
    {
      return *this;
    }
  };

}  // namespace LinearAlgebra
