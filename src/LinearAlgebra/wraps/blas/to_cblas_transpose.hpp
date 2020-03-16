// Role:
// - To_CBlas_Transpose_v: convert a Matrix_Unary_Op_Enum into a CBLAS_TRANSPOSE compatible value
// - Support_CBlas_Transpose_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"  // for _matrix_unary_op_t_<Matrix_Unary_Op_Enum::XXX>
#include "LinearAlgebra/meta/is_complete.hpp"
#include "LinearAlgebra/wraps/blas/blas_config.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    // SFINEA friendly (<- do not use static_assert) conversion:
    //
    // from Matrix_Unary_Op_Enum to CBLAS_TRANSPOSE
    //
    // Note: must be SFINEA friendly as it is used by expr() to check
    // subroutine existence
    //
    template <Matrix_Unary_Op_Enum OP_M>
    struct To_CBlas_Transpose;

    template <>
    struct To_CBlas_Transpose<Matrix_Unary_Op_Enum::Identity>
    {
      static constexpr CBLAS_TRANSPOSE value = CblasNoTrans;
    };
    template <>
    struct To_CBlas_Transpose<Matrix_Unary_Op_Enum::Transpose>
    {
      static constexpr CBLAS_TRANSPOSE value = CblasTrans;
    };
    template <>
    struct To_CBlas_Transpose<Matrix_Unary_Op_Enum::TransConj>
    {
      static constexpr CBLAS_TRANSPOSE value = CblasConjNoTrans;
    };

    template <Matrix_Unary_Op_Enum OP_M>
    constexpr auto To_CBlas_Transpose_v = To_CBlas_Transpose<OP_M>::value;

    template <Matrix_Unary_Op_Enum OP_M>
    constexpr auto Support_CBlas_Transpose_v = Is_Complete<To_CBlas_Transpose<OP_M>>::value;

  }
}
