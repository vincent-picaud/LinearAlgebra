// Role:
// - To_Lapack_Transpose_v: convert a Matrix_Unary_Op_Enum into a LAPACK_TRANSPOSE compatible value
// - Support_Lapack_Transpose_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/lapack/lapack_config.hpp"

#if !(HAS_LAPACK)
#error
#endif

#include "LinearAlgebra/expr/expr_tags.hpp"  // for _matrix_unary_op_t_<Matrix_Unary_Op_Enum::XXX>
#include "LinearAlgebra/utils/is_complete.hpp"

namespace LinearAlgebra
{
  namespace Lapack
  {
    template <Matrix_Unary_Op_Enum OP_M>
    struct To_Lapack_Transpose;

    //================================================================

    template <>
    struct To_Lapack_Transpose<Matrix_Unary_Op_Enum::Identity>
    {
      static constexpr Lapack_Transpose_Enum value = Identity;
    };
    template <>
    struct To_Lapack_Transpose<Matrix_Unary_Op_Enum::Transpose>
    {
      static constexpr Lapack_Transpose_Enum value = Transpose;
    };
    template <>
    struct To_Lapack_Transpose<Matrix_Unary_Op_Enum::TransConj>
    {
      static constexpr Lapack_Transpose_Enum value = TransConj;
    };

    //================================================================
    //
    // Syntactic sugar
    //

    template <Matrix_Unary_Op_Enum OP_M>
    constexpr auto To_Lapack_Transpose_v = To_Lapack_Transpose<OP_M>::value;

    template <Matrix_Unary_Op_Enum OP_M>
    constexpr auto Support_Lapack_Transpose_v = Is_Complete_v<To_Lapack_Transpose<OP_M>>;

  }  // namespace Lapack
}  // namespace LinearAlgebra
