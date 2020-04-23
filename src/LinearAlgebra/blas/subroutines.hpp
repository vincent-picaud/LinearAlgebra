#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if !(HAS_BLAS)
#error
#endif

#include <ccomplex>
#include <cstddef>

// A (temporary) patch to see which routines are used
// (comment me out in production)
// #define BLAS_DEBUG

#ifdef BLAS_DEBUG
#include <iostream>  // For debug

#define BLAS_DEBUG_LOG std::cerr << __PRETTY_FUNCTION__ << std::endl;

#else

#define BLAS_DEBUG_LOG

#endif

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
  // - [ ] : SUBROUTINE _SCAL ( N,  ALPHA, X, INCX )                                       S, D, C, Z, CS, ZD
  // - [X] : SUBROUTINE _COPY ( N,         X, INCX, Y, INCY )                              S, D, C, Z
  // - [ ] : SUBROUTINE _AXPY ( N,  ALPHA, X, INCX, Y, INCY )                              S, D, C, Z
  // - [X] : FUNCTION   _DOT  ( N,         X, INCX, Y, INCY )                              S, D, DS
  // - [ ] : FUNCTION   _DOTU ( N,         X, INCX, Y, INCY )                              C, Z
  // - [X] : FUNCTION   _DOTC ( N,         X, INCX, Y, INCY )                              C, Z
  // - [ ] : FUNCTION   __DOT ( N,  ALPHA, X, INCX, Y, INCY )                              SDS
  // - [ ] : FUNCTION   _NRM2 ( N,         X, INCX )                                       S, D, SC, DZ
  // - [ ] : FUNCTION   _ASUM ( N,         X, INCX )                                       S, D, SC, DZ
  // - [ ] : FUNCTION   I_AMAX( N,         X, INCX )                                       S, D, C, Z

  // Xnrm2
  //================
  //
  static inline auto
  nrm2(const std::size_t n, const float *x, const std::size_t incx)
  {
    return cblas_snrm2(n, x, incx);
  }
  static inline auto
  nrm2(const std::size_t n, const double *x, const std::size_t incx)
  {
    return cblas_dnrm2(n, x, incx);
  }
  static inline auto
  nrm2(const std::size_t n, const std::complex<float> *x, const std::size_t incx)
  {
    return cblas_scnrm2(n, x, incx);
  }
  static inline auto
  nrm2(const std::size_t n, const std::complex<double> *x, const std::size_t incx)
  {
    return cblas_dznrm2(n, x, incx);
  }

  // Xdot
  //================
  //
  static inline auto
  dot(const std::size_t n,
      const float *x,
      const std::size_t incx,
      const float *y,
      const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    return cblas_sdot(n, x, incx, y, incy);
  }
  static inline auto
  dot(const std::size_t n,
      const double *x,
      const std::size_t incx,
      const double *y,
      const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    return cblas_ddot(n, x, incx, y, incy);
  }
  static inline std::complex<float>
  dot(const std::size_t n,
      const std::complex<float> *x,
      const std::size_t incx,
      const std::complex<float> *y,
      const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    // dotc x^H.y <- hermitian inner prod.
    return cblas_cdotc(n, x, incx, y, incy);
  }
  static inline std::complex<double>
  dot(const std::size_t n,
      const std::complex<double> *x,
      const std::size_t incx,
      const std::complex<double> *y,
      const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    // dotc x^H.y <- hermitian inner prod.
    return cblas_zdotc(n, x, incx, y, incy);
  }

  // Xcopy
  //================
  //
  static inline void
  copy(
      const std::size_t n, const float *x, const std::size_t incx, float *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_scopy(n, x, incx, y, incy);
  }

  static inline void
  copy(const std::size_t n,
       const double *x,
       const std::size_t incx,
       double *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_dcopy(n, x, incx, y, incy);
  }

  static inline void
  copy(const std::size_t n,
       const std::complex<float> *x,
       const std::size_t incx,
       std::complex<float> *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_ccopy(n, x, incx, y, incy);
  }

  static inline void
  copy(const std::size_t n,
       const std::complex<double> *x,
       const std::size_t incx,
       std::complex<double> *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_zcopy(n, x, incx, y, incy);
  }

  /////////////
  // Level 2 //
  /////////////
  //                 options            dim   b-width scalar matrix  vector   scalar vector   prefixes
  //
  // - [X] : _GEMV (        TRANS,      M, N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D, C, Z
  // - [ ] : _GBMV (        TRANS,      M, N, KL, KU, ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D, C, Z
  // - [ ] : _HEMV ( UPLO,                 N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _HBMV ( UPLO,                 N, K,      ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) C, Z
  // - [ ] : _HPMV ( UPLO,                 N,         ALPHA, AP,     X, INCX, BETA,  Y, INCY ) C, Z
  // - [X] : _SYMV ( UPLO,                 N,         ALPHA, A, LDA, X, INCX, BETA,  Y, INCY ) S, D
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

  // Xtrmv: y=α.M.x, M triangular
  //================
  //
  static inline void
  trmv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const float *a,
       const std::size_t lda,
       float *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_strmv(order, uplo, trans, diag, n, a, lda, x, incx);
  }
  static inline void
  trmv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const double *a,
       const std::size_t lda,
       double *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_dtrmv(order, uplo, trans, diag, n, a, lda, x, incx);
  }
  static inline void
  trmv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const std::complex<float> *a,
       const std::size_t lda,
       std::complex<float> *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_ctrmv(order, uplo, trans, diag, n, a, lda, x, incx);
  }
  static inline void
  trmv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const std::complex<double> *a,
       const std::size_t lda,
       std::complex<double> *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_ztrmv(order, uplo, trans, diag, n, a, lda, x, incx);
  }

  // Xtrsv: y=α.inverse(M).x, M triangular
  //================
  //
  static inline void
  trsv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const float *a,
       const std::size_t lda,
       float *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_strsv(order, uplo, trans, diag, n, a, lda, x, incx);
  }
  static inline void
  trsv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const double *a,
       const std::size_t lda,
       double *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_dtrsv(order, uplo, trans, diag, n, a, lda, x, incx);
  }
  static inline void
  trsv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const std::complex<float> *a,
       const std::size_t lda,
       std::complex<float> *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_ctrsv(order, uplo, trans, diag, n, a, lda, x, incx);
  }
  static inline void
  trsv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const enum CBLAS_TRANSPOSE trans,
       const enum CBLAS_DIAG diag,
       const std::size_t n,
       const std::complex<double> *a,
       const std::size_t lda,
       std::complex<double> *x,
       const std::size_t incx)
  {
    BLAS_DEBUG_LOG;

    cblas_ztrsv(order, uplo, trans, diag, n, a, lda, x, incx);
  }

  // Xsymv: y=α.M.x+βy, M symmetric
  //================
  // CAVEAT: blas only provides float, double
  //
  static inline void
  symv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const std::size_t n,
       const float alpha,
       const float *a,
       const std::size_t lda,
       const float *x,
       const std::size_t incx,
       const float beta,
       float *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_ssymv(order, uplo, n, alpha, a, lda, x, incx, beta, y, incy);
  }
  static inline void
  symv(const enum CBLAS_ORDER order,
       const enum CBLAS_UPLO uplo,
       const std::size_t n,
       const double alpha,
       const double *a,
       const std::size_t lda,
       const double *x,
       const std::size_t incx,
       const double beta,
       double *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_dsymv(order, uplo, n, alpha, a, lda, x, incx, beta, y, incy);
  }

  // Xgemv: y=α.M.x+βy
  //================
  //
  static inline void
  gemv(const enum CBLAS_ORDER order,
       const enum CBLAS_TRANSPOSE trans,
       const std::size_t m,
       const std::size_t n,
       const float alpha,
       const float *a,
       const std::size_t lda,
       const float *x,
       const std::size_t incx,
       const float beta,
       float *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_sgemv(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
  }
  static inline void
  gemv(const enum CBLAS_ORDER order,
       const enum CBLAS_TRANSPOSE trans,
       const std::size_t m,
       const std::size_t n,
       const double alpha,
       const double *a,
       const std::size_t lda,
       const double *x,
       const std::size_t incx,
       const double beta,
       double *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_dgemv(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
  }
  static inline void
  gemv(const enum CBLAS_ORDER order,
       const enum CBLAS_TRANSPOSE trans,
       const std::size_t m,
       const std::size_t n,
       const std::complex<float> &alpha,
       const std::complex<float> *a,
       const std::size_t lda,
       const std::complex<float> *x,
       const std::size_t incx,
       const std::complex<float> &beta,
       std::complex<float> *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_cgemv(order, trans, m, n, &alpha, a, lda, x, incx, &beta, y, incy);
  }
  static inline void
  gemv(const enum CBLAS_ORDER order,
       const enum CBLAS_TRANSPOSE trans,
       const std::size_t m,
       const std::size_t n,
       const std::complex<double> &alpha,
       const std::complex<double> *a,
       const std::size_t lda,
       const std::complex<double> *x,
       const std::size_t incx,
       const std::complex<double> &beta,
       std::complex<double> *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_zgemv(order, trans, m, n, &alpha, a, lda, x, incx, &beta, y, incy);
  }

  /////////////
  // Level 2 //
  /////////////
  //
  //                 options                          dim      scalar matrix  matrix  scalar matrix  prefixes
  //
  // - [ ] : _GEMM (             TRANSA, TRANSB,      M, N, K, ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _SYMM ( SIDE, UPLO,                      M, N,    ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _HEMM ( SIDE, UPLO,                      M, N,    ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) C, Z
  // - [X] : _SYRK (       UPLO, TRANS,                  N, K, ALPHA, A, LDA,         BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _HERK (       UPLO, TRANS,                  N, K, ALPHA, A, LDA,         BETA,  C, LDC ) C, Z
  // - [ ] : _SYR2K(       UPLO, TRANS,                  N, K, ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) S, D, C, Z
  // - [ ] : _HER2K(       UPLO, TRANS,                  N, K, ALPHA, A, LDA, B, LDB, BETA,  C, LDC ) C, Z
  // - [ ] : _TRMM ( SIDE, UPLO, TRANSA,        DIAG, M, N,    ALPHA, A, LDA, B, LDB )                S, D, C, Z
  // - [ ] : _TRSM ( SIDE, UPLO, TRANSA,        DIAG, M, N,    ALPHA, A, LDA, B, LDB )                S, D, C, Z

  //
  // Xsyrk:
  //
  // C := alpha*A*A' + beta*C,
  // or
  // C := alpha*A'*A + beta*C,
  //
  static inline void
  syrk(const enum CBLAS_ORDER Order,
       const enum CBLAS_UPLO Uplo,
       const enum CBLAS_TRANSPOSE Trans,
       const std::size_t N,
       const std::size_t K,
       const float alpha,
       const float *A,
       const std::size_t lda,
       const float beta,
       float *C,
       const std::size_t ldc)
  {
    BLAS_DEBUG_LOG;

    cblas_ssyrk(Order, Uplo, Trans, N, K, alpha, A, lda, beta, C, ldc);
  }
  static inline void
  syrk(const enum CBLAS_ORDER Order,
       const enum CBLAS_UPLO Uplo,
       const enum CBLAS_TRANSPOSE Trans,
       const std::size_t N,
       const std::size_t K,
       const double alpha,
       const double *A,
       const std::size_t lda,
       const double beta,
       double *C,
       const std::size_t ldc)
  {
    BLAS_DEBUG_LOG;

    cblas_dsyrk(Order, Uplo, Trans, N, K, alpha, A, lda, beta, C, ldc);
  }
  static inline void
  syrk(const enum CBLAS_ORDER Order,
       const enum CBLAS_UPLO Uplo,
       const enum CBLAS_TRANSPOSE Trans,
       const std::size_t N,
       const std::size_t K,
       const std::complex<float> &alpha,
       const std::complex<float> *A,
       const std::size_t lda,
       const std::complex<float> &beta,
       std::complex<float> *C,
       const std::size_t ldc)
  {
    BLAS_DEBUG_LOG;

    cblas_csyrk(Order, Uplo, Trans, N, K, &alpha, A, lda, &beta, C, ldc);
  }
  static inline void
  syrk(const enum CBLAS_ORDER Order,
       const enum CBLAS_UPLO Uplo,
       const enum CBLAS_TRANSPOSE Trans,
       const std::size_t N,
       const std::size_t K,
       const std::complex<double> &alpha,
       const std::complex<double> *A,
       const std::size_t lda,
       const std::complex<double> &beta,
       std::complex<double> *C,
       const std::size_t ldc)
  {
    BLAS_DEBUG_LOG;

    cblas_zsyrk(Order, Uplo, Trans, N, K, &alpha, A, lda, &beta, C, ldc);
  }
}
