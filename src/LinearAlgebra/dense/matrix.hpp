// TODO: for hermitian matrices, check that diagonal is real
#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/matrix_storage_scheme.hpp"
#include "LinearAlgebra/dense/memory_chunk.hpp"
#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

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

    template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
              Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
              typename LEADING_DIMENSION>
    constexpr bool sanity_check_v =
        is_structure_mask_combination_allowed_v<SPECIAL_STRUCTURE, MASK>and
            Is_Std_Integral_Constant_Size_Or_Std_Size_v<N_TYPE>and
                Is_Std_Integral_Constant_Size_Or_Std_Size_v<M_TYPE>and
                    Is_Std_Integral_Constant_Size_Or_Std_Size_v<LEADING_DIMENSION>;

  }

  // Below concrete implementations Default_Matrix_Crtp<> of are defined:
  //
  // - Default_Matrix
  // - Default_Matrix_View
  // - Default_Matrix_Const_View
  //

  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix;

  template <typename T, LinearAlgebra::Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            LinearAlgebra::Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  struct Crtp_Type_Traits<
      LinearAlgebra::Default_Matrix<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Matrix_Storage_Scheme<MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>;
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

  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix
      : public Dense_Matrix_Crtp<
            Default_Matrix<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>
  {
    static_assert(Default_Matrix_Detail::sanity_check_v<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE,
                                                        LEADING_DIMENSION>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Matrix_Crtp<
        Default_Matrix<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>;

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
    // Members //
    /////////////
    //
   protected:
    //////////////////
    // Constructors //
    //////////////////
    //
   public:
    Default_Matrix() : base_type(storage_scheme_type()) {}
    Default_Matrix(const N_TYPE n, const M_TYPE m, const LEADING_DIMENSION ld)
        : base_type(storage_scheme_type(n, m, ld))
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }
    Default_Matrix(const N_TYPE n, const M_TYPE m) : base_type(storage_scheme_type(n, m))
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }

    ////////////////////
    // Public Methods //
    ////////////////////
    //
   public:
  };
  //****************************************************************

  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix_View;

  template <typename T, LinearAlgebra::Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            LinearAlgebra::Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Matrix_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE,
                                                             M_TYPE, LEADING_DIMENSION>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Matrix_Storage_Scheme<MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>;
    using memory_chunk_type = LinearAlgebra::View_Default_Memory_Chunk<
        T, typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

    using matrix_special_structure_type =
        std::integral_constant<LinearAlgebra::Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>;
  };

  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix_View
      : public Dense_Matrix_Crtp<
            Default_Matrix_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>
  {
    static_assert(Default_Matrix_Detail::sanity_check_v<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE,
                                                        LEADING_DIMENSION>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Matrix_Crtp<
        Default_Matrix_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>;

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
    // Design:
    //   Do *not* start to define constructors like
    // #+begin_src cpp
    // template <size_t N_OTHER>
    // Default_Matrix_View(const Default_Matrix<T, SPECIAL_STRUCTURE, N_OTHER> &v)
    //     : base_type(storage_scheme_type(),
    //                 memory_chunk_type(v._memory_chunk.data())) {
    //   static_assert(base_type::required_capacity() <= v.required_capacity());
    // }
    // #+end_src
    //
    // Reason: this would add artificial and useless strong couplings/dependencies
    //
   public:
    Default_Matrix_View(T* data) : base_type(storage_scheme_type(), data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }
    Default_Matrix_View(T* data, const N_TYPE n, const M_TYPE m, const LEADING_DIMENSION ld)
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
  };

  //================================================================

  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix_Const_View;

  template <typename T, LinearAlgebra::Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            LinearAlgebra::Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  struct Crtp_Type_Traits<LinearAlgebra::Default_Matrix_Const_View<
      T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>
  {
    using storage_scheme_type =
        LinearAlgebra::Default_Matrix_Storage_Scheme<MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>;
    using memory_chunk_type = LinearAlgebra::Const_View_Default_Memory_Chunk<
        T, typename storage_scheme_type::required_capacity_type>;

    using element_type = typename memory_chunk_type::element_type;

    using I_size_type = typename storage_scheme_type::I_size_type;
    using J_size_type = typename storage_scheme_type::J_size_type;

    using leading_dimension_type = typename storage_scheme_type::leading_dimension_type;

    using matrix_special_structure_type =
        std::integral_constant<LinearAlgebra::Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>;
  };

  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  class Default_Matrix_Const_View
      : public Dense_Matrix_Crtp<Default_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE,
                                                           M_TYPE, LEADING_DIMENSION>>
  {
    static_assert(Default_Matrix_Detail::sanity_check_v<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE,
                                                        LEADING_DIMENSION>);

    ///////////
    // Types //
    ///////////
    //
   public:
    using base_type = Dense_Matrix_Crtp<
        Default_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>>;

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
    Default_Matrix_Const_View(const T* data) : base_type(storage_scheme_type(), data)
    {
      assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
             (base_type::I_size() == base_type::J_size()));
    }
    // Default_Matrix_Const_View(const T* data, const N_TYPE n, const M_TYPE m,
    //                           const LEADING_DIMENSION ld)
    //     : base_type(storage_scheme_type(n, m, ld), data)
    // {
    //   assert((not Matrix_Special_Structure_Imposes_Square_Matrix<SPECIAL_STRUCTURE>::value) ||
    //          (base_type::I_size() == base_type::J_size()));
    // }

    Default_Matrix_Const_View(const T* data, const N_TYPE n, const M_TYPE m,
                              const LEADING_DIMENSION ld)
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
  };

  ////////////////
  // Some views //
  ////////////////

  // const views
  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  auto
  create_view(const T* data,
              const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
              const Default_Matrix_Storage_Scheme<MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>&
                  default_matrix_storage_scheme)
  {
    return Default_Matrix_Const_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>(
        default_matrix_storage_scheme, data);
  }

  // mutable views
  template <typename T, Matrix_Special_Structure_Enum SPECIAL_STRUCTURE,
            Matrix_Storage_Mask_Enum MASK, typename N_TYPE, typename M_TYPE,
            typename LEADING_DIMENSION>
  auto
  create_view(T* data,
              const std::integral_constant<Matrix_Special_Structure_Enum, SPECIAL_STRUCTURE>,
              const Default_Matrix_Storage_Scheme<MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>&
                  default_matrix_storage_scheme)
  {
    return Default_Matrix_View<T, SPECIAL_STRUCTURE, MASK, N_TYPE, M_TYPE, LEADING_DIMENSION>(
        default_matrix_storage_scheme, data);
  }

  ////////////////
  // Some Alias //
  ////////////////
  //

  //================

  template <typename T, size_t N, size_t M>
  using Tiny_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::None, Matrix_Storage_Mask_Enum::None,
                     std::integral_constant<std::size_t, N>, std::integral_constant<std::size_t, M>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Matrix = Default_Matrix<T, Matrix_Special_Structure_Enum::None,
                                Matrix_Storage_Mask_Enum::None, size_t, size_t, size_t>;

  //================ Triangular_Strict

  // Lower
  template <typename T, size_t N, size_t M>
  using Tiny_Lower_Triangular_Strict_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Lower_Strict, std::integral_constant<std::size_t, N>,
                     std::integral_constant<std::size_t, M>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Lower_Triangular_Strict_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Lower_Strict, size_t, size_t, size_t>;

  // Upper
  template <typename T, size_t N, size_t M>
  using Tiny_Upper_Triangular_Strict_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Upper_Strict, std::integral_constant<std::size_t, N>,
                     std::integral_constant<std::size_t, M>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Upper_Triangular_Strict_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Triangular_Strict,
                     Matrix_Storage_Mask_Enum::Upper_Strict, size_t, size_t, size_t>;

  //================ Unit_Triangular

  // Lower
  template <typename T, size_t N, size_t M>
  using Tiny_Lower_Unit_Triangular_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Lower_Strict, std::integral_constant<std::size_t, N>,
                     std::integral_constant<std::size_t, M>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Lower_Unit_Triangular_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Lower_Strict, size_t, size_t, size_t>;

  // Upper
  template <typename T, size_t N, size_t M>
  using Tiny_Upper_Unit_Triangular_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Upper_Strict, std::integral_constant<std::size_t, N>,
                     std::integral_constant<std::size_t, M>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Upper_Unit_Triangular_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Unit_Triangular,
                     Matrix_Storage_Mask_Enum::Upper_Strict, size_t, size_t, size_t>;

  //================ Symmetric (are square)

  template <typename T, size_t N>
  using Tiny_Symmetric_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Symmetric, Matrix_Storage_Mask_Enum::Lower,
                     std::integral_constant<std::size_t, N>, std::integral_constant<std::size_t, N>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Symmetric_Matrix = Default_Matrix<T, Matrix_Special_Structure_Enum::Symmetric,
                                          Matrix_Storage_Mask_Enum::Lower, size_t, size_t, size_t>;

  //================ Hermitian (are square)

  template <typename T, size_t N>
  using Tiny_Hermitian_Matrix =
      Default_Matrix<T, Matrix_Special_Structure_Enum::Hermitian, Matrix_Storage_Mask_Enum::Lower,
                     std::integral_constant<std::size_t, N>, std::integral_constant<std::size_t, N>,
                     std::integral_constant<std::size_t, N>>;

  template <typename T>
  using Hermitian_Matrix = Default_Matrix<T, Matrix_Special_Structure_Enum::Hermitian,
                                          Matrix_Storage_Mask_Enum::Lower, size_t, size_t, size_t>;

}
