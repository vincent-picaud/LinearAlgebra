// Check if a vector, matrix etc... has a static dimension
//
// Main usage so far is to catch static vector, matrix in expr/ to
// redirect them to the generic routine instead of the BLAS one
//
// Compared to "Has_Static_I_Size" etc... It is more generic. By example to check if OBJ has static dimension you can use
//
//    Has_Static_Dimension<OBJ>
//
// for vectors and matrices
//
// With Has_Static_I_Size the test are _different_:
//
//    Has_Static_Size<OBJ>                             for vector
//
//    Has_Static_I_Size<OBJ> && Has_Static_J_Size<OBJ> for matrix
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

#include "LinearAlgebra/utils/is_std_integral_constant.hpp"

#include <type_traits>

namespace LinearAlgebra
{
  //
  // Default = false
  //
  template <typename IMPL, typename ENABLE = void>
  struct Has_Static_Dimension : std::false_type
  {
  };

  //
  // Vector
  //
  template <typename IMPL>
  struct Has_Static_Dimension<IMPL, std::enable_if_t<Is_Crtp_Interface_Of_v<Vector_Crtp, IMPL>>>
      : std::conditional_t<
            Is_Std_Integral_Constant_Of_Type_v<std::size_t, typename IMPL::size_type>,
            std::true_type, std::false_type>
  {
  };

  //
  // Matrix
  //
  template <typename IMPL>
  struct Has_Static_Dimension<IMPL, std::enable_if_t<Is_Crtp_Interface_Of_v<Matrix_Crtp, IMPL>>>
      : std::conditional_t<
            Is_Std_Integral_Constant_Of_Type_v<std::size_t, typename IMPL::I_size_type> and
                Is_Std_Integral_Constant_Of_Type_v<std::size_t, typename IMPL::J_size_type>,
            std::true_type, std::false_type>
  {
  };

  //
  // Syntactic sugar
  //
  template <typename IMPL>
  constexpr auto Has_Static_Dimension_v = Has_Static_Dimension<IMPL>::value;

  //================================================================

  //
  // Any_Has_Static_Dimension
  //
  template <typename... IMPL>
  constexpr auto Any_Has_Static_Dimension_v = ((Has_Static_Dimension<IMPL>::value) or ...);

}
