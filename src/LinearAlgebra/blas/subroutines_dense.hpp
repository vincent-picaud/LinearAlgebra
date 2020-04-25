//
// Wraps "subroutines" with dense (vector/matrix) objects
//
// This is the "abstract subroutine" one must preferably use.
//
#pragma once

// Note: this a quite "abstract" header, hence we include "blas.hpp"
// and dense vector & matrix headers
//
#include <cblas.h>
#include "LinearAlgebra/blas/blas.hpp"

#include "LinearAlgebra/blas/subroutines.hpp"
#include "LinearAlgebra/blas/to_cblas_diag.hpp"
#include "LinearAlgebra/blas/to_cblas_transpose.hpp"
#include "LinearAlgebra/blas/to_cblas_uplo.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/utils/always.hpp"
#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

namespace LinearAlgebra::Blas
{
  /////////////
  // Level 1 //
  /////////////
  //
  //                            dim scalar vector   vector   scalars              5-element prefixes
  //
  // - [ ] : SUBROUTINE _ROTG (                                      A, B, C, S )          S, D
  // - [ ] : SUBROUTINE _ROTMG(                              D1, D2, A, B,        PARAM )  S, D
  // - [ ] : SUBROUTINE _ROT  ( N,         X, INCX, Y, INCY,               C, S )          S, D
  // - [ ] : SUBROUTINE _ROTM ( N,         X, INCX, Y, INCY,                      PARAM )  S, D
  // - [ ] : SUBROUTINE _SWAP ( N,         X, INCX, Y, INCY )                              S, D, C, Z
  // - [X] : SUBROUTINE _SCAL ( N,  ALPHA, X, INCX )                                       S, D, C, Z, CS, ZD
  // - [X] : SUBROUTINE _COPY ( N,         X, INCX, Y, INCY )                              S, D, C, Z
  // - [ ] : SUBROUTINE _AXPY ( N,  ALPHA, X, INCX, Y, INCY )                              S, D, C, Z
  // - [ ] : FUNCTION   _DOT  ( N,         X, INCX, Y, INCY )                              S, D, DS
  // - [ ] : FUNCTION   _DOTU ( N,         X, INCX, Y, INCY )                              C, Z
  // - [ ] : FUNCTION   _DOTC ( N,         X, INCX, Y, INCY )                              C, Z
  // - [ ] : FUNCTION   __DOT ( N,  ALPHA, X, INCX, Y, INCY )                              SDS
  // - [ ] : FUNCTION   _NRM2 ( N,         X, INCX )                                       S, D, SC, DZ
  // - [ ] : FUNCTION   _ASUM ( N,         X, INCX )                                       S, D, SC, DZ
  // - [ ] : FUNCTION   I_AMAX( N,         X, INCX )                                       S, D, C, Z

  //==== copy ====
  //
  template <typename V0_IMPL, typename V1_IMPL>
  auto
  copy(const Dense_Vector_Crtp<V1_IMPL>& V1, Dense_Vector_Crtp<V0_IMPL>& V0)
      -> std::enable_if_t<Always_True_v<
          decltype(Blas::copy(V0.size(), V1.data(), V1.increment(), V0.data(), V0.increment()))>>
  {
    assert(V0.size() == V1.size());

    Blas::copy(V0.size(), V1.data(), V1.increment(), V0.data(), V0.increment());
  }

  //==== scal ====
  //
  template <typename V_IMPL>
  auto
  scal(const Element_Type_t<V_IMPL>& alpha, Dense_Vector_Crtp<V_IMPL>& V) -> std::enable_if_t<
      Always_True_v<decltype(Blas::scal(V.size(), alpha, V.data(), V.increment()))>>
  {
    Blas::scal(V.size(), alpha, V.data(), V.increment());
  }

  /////////////
  // Level 2 //
  /////////////
  //                 options            dim   b-width scalar matrix  vector   scalar vector   prefixes
  //
  // - [ ] : _GEMV (        TRANS,      M, N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D, C, Z
  // - [ ] : _GBMV (        TRANS,      M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D, C, Z
  // - [ ] : _HEMV ( UPLO,                 N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _HBMV ( UPLO,                 N, K,      ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _HPMV ( UPLO,                 N,         ALPHA, AP,     X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _SYMV ( UPLO,                 N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D
  // - [ ] : _SBMV ( UPLO,                 N, K,      ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D
  // - [ ] : _SPMV ( UPLO,                 N,         ALPHA, AP,     X, INCX, BETA,  Y, INCY ) S, D
  // - [X] : _TRMV ( UPLO, TRANS, DIAG,    N,                A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TBMV ( UPLO, TRANS, DIAG,    N, K,             A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TPMV ( UPLO, TRANS, DIAG,    N,                AP,     X, INCX )                 S, D, C, Z
  // - [X] : _TRSV ( UPLO, TRANS, DIAG,    N,                A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TBSV ( UPLO, TRANS, DIAG,    N, K,             A, LDA, X, INCX )                 S, D, C, Z
  // - [ ] : _TPSV ( UPLO, TRANS, DIAG,    N,                AP,     X, INCX )                 S, D, C, Z
  //
  // - [ ] :         options            dim   scalar vector   vector   matrix  prefixes
  //
  // - [ ] : _GER  (                    M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) S, D
  // - [ ] : _GERU (                    M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z
  // - [ ] : _GERC (                    M, N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z
  // - [ ] : _HER  ( UPLO,                 N, ALPHA, X, INCX,          A, LDA ) C, Z
  // - [ ] : _HPR  ( UPLO,                 N, ALPHA, X, INCX,          AP )     C, Z
  // - [ ] : _HER2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, A, LDA ) C, Z
  // - [ ] : _HPR2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, AP )     C, Z
  // - [ ] : _SYR  ( UPLO,                 N, ALPHA, X, INCX,          A, LDA ) S, D
  // - [ ] : _SPR  ( UPLO,                 N, ALPHA, X, INCX,          AP )     S, D
  // - [ ] : _SYR2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, A, LDA ) S, D
  // - [ ] : _SPR2 ( UPLO,                 N, ALPHA, X, INCX, Y, INCY, AP )     S, D
  // - [ ] :

  //==== trmv ====
  //
  template <Matrix_Unary_Op_Enum OP, typename X_IMPL, typename M_IMPL>
  auto
  trmv(const _matrix_unary_op_t_<OP> op,
       const Dense_Matrix_Crtp<M_IMPL>& M,
       Dense_Vector_Crtp<X_IMPL>& x)
      -> std::enable_if_t<Always_True_v<decltype(Blas::trmv(CblasColMajor,
                                                            To_CBlas_UpLo_v<M_IMPL>,
                                                            To_CBlas_Transpose_v<OP>,
                                                            To_CBlas_Diag_v<M_IMPL>,
                                                            M.I_size(),
                                                            M.data(),
                                                            M.leading_dimension(),
                                                            x.data(),
                                                            x.increment()))>>
  {
    Blas::trmv(CblasColMajor,
               To_CBlas_UpLo_v<M_IMPL>,
               To_CBlas_Transpose_v<OP>,
               To_CBlas_Diag_v<M_IMPL>,
               M.I_size(),
               M.data(),
               M.leading_dimension(),
               x.data(),
               x.increment());
  }

  //==== trsv ====
  //
  template <Matrix_Unary_Op_Enum OP, typename X_IMPL, typename M_IMPL>
  auto
  trsv(const _matrix_unary_op_t_<OP> op,
       const Dense_Matrix_Crtp<M_IMPL>& M,
       Dense_Vector_Crtp<X_IMPL>& x)
      -> std::enable_if_t<Always_True_v<decltype(Blas::trsv(CblasColMajor,
                                                            To_CBlas_UpLo_v<M_IMPL>,
                                                            To_CBlas_Transpose_v<OP>,
                                                            To_CBlas_Diag_v<M_IMPL>,
                                                            M.I_size(),
                                                            M.data(),
                                                            M.leading_dimension(),
                                                            x.data(),
                                                            x.increment()))>>
  {
    Blas::trsv(CblasColMajor,
               To_CBlas_UpLo_v<M_IMPL>,
               To_CBlas_Transpose_v<OP>,
               To_CBlas_Diag_v<M_IMPL>,
               M.I_size(),
               M.data(),
               M.leading_dimension(),
               x.data(),
               x.increment());
  }
}  // namespace LinearAlgebra::Blas
