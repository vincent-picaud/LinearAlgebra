#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if !(HAS_BLAS)
#error
#endif

#include <ccomplex>
#include <cstddef>

// A (temporary) patch to see which routines are used
// (comment me out in production)
#define BLAS_DEBUG

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

  // Xcopy
  //================
  //
  void
  copy(const std::size_t n, const float *x, const std::size_t incx, float *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_scopy(n, x, incx, y, incy);
  }

  void
  copy(const std::size_t n, const double *x, const std::size_t incx, double *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_dcopy(n, x, incx, y, incy);
  }

  void
  copy(const std::size_t n, const std::complex<float> *x, const std::size_t incx,
       std::complex<float> *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_ccopy(n, x, incx, y, incy);
  }

  void
  copy(const std::size_t n, const std::complex<double> *x, const std::size_t incx,
       std::complex<double> *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_zcopy(n, x, incx, y, incy);
  }

  /////////////
  // Level 2 //
  /////////////

  // Xsymv: y=α.M.x+βy, M symmetric
  //================
  // CAVEAT: only float, double
  //
  void
  symv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo, const std::size_t n,
       const float alpha, const float *a, const std::size_t lda, const float *x,
       const std::size_t incx, const float beta, float *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_ssymv(order, uplo, n, alpha, a, lda, x, incx, beta, y, incy);
  }
  void
  symv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo, const std::size_t n,
       const double alpha, const double *a, const std::size_t lda, const double *x,
       const std::size_t incx, const double beta, double *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_dsymv(order, uplo, n, alpha, a, lda, x, incx, beta, y, incy);
  }

  // Xgemv: y=α.M.x+βy
  //================
  //
  void
  gemv(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE trans, const std::size_t m,
       const std::size_t n, const float alpha, const float *a, const std::size_t lda,
       const float *x, const std::size_t incx, const float beta, float *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_sgemv(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
  }
  void
  gemv(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE trans, const std::size_t m,
       const std::size_t n, const double alpha, const double *a, const std::size_t lda,
       const double *x, const std::size_t incx, const double beta, double *y,
       const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_dgemv(order, trans, m, n, alpha, a, lda, x, incx, beta, y, incy);
  }
  void
  gemv(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE trans, const std::size_t m,
       const std::size_t n, const std::complex<float> alpha, const std::complex<float> *a,
       const std::size_t lda, const std::complex<float> *x, const std::size_t incx,
       const std::complex<float> beta, std::complex<float> *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_cgemv(order, trans, m, n, &alpha, a, lda, x, incx, &beta, y, incy);
  }
  void
  gemv(const enum CBLAS_ORDER order, const enum CBLAS_TRANSPOSE trans, const std::size_t m,
       const std::size_t n, const std::complex<double> alpha, const std::complex<double> *a,
       const std::size_t lda, const std::complex<double> *x, const std::size_t incx,
       const std::complex<double> beta, std::complex<double> *y, const std::size_t incy)
  {
    BLAS_DEBUG_LOG;

    cblas_zgemv(order, trans, m, n, &alpha, a, lda, x, incx, &beta, y, incy);
  }
}
