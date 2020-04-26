// Role:
// - To_CBlas_Transpose_v: convert a Matrix_Unary_Op_Enum into a CBLAS_TRANSPOSE compatible value
// - Support_CBlas_Transpose_v: compile-time if this conversion is possible
//
#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if !(HAS_BLAS)
#error
#endif

#include "LinearAlgebra/expr/expr_tags.hpp"  // for _matrix_unary_op_t_<Matrix_Unary_Op_Enum::XXX>
#include "LinearAlgebra/utils/is_complete.hpp"

namespace LinearAlgebra
{
  namespace Blas
  {
    template <Matrix_Unary_Op_Enum OP_M>
    struct To_CBlas_Transpose;

    //================================================================

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

    //================================================================
    //
    // Syntactic sugar
    //

    template <Matrix_Unary_Op_Enum OP_M>
    constexpr auto To_CBlas_Transpose_v = To_CBlas_Transpose<OP_M>::value;

    template <Matrix_Unary_Op_Enum OP_M>
    constexpr auto Support_CBlas_Transpose_v = Is_Complete_v<To_CBlas_Transpose<OP_M>>;

  }  // namespace Blas
}  // namespace LinearAlgebra
