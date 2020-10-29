#pragma once

#include "LinearAlgebra/lapack/lapack_config.hpp"

#if !(HAS_LAPACK)
#error
#endif

#include "LinearAlgebra/lapack/lapack_enum.hpp"

#include <ccomplex>
#include <cstddef>

// A (temporary) patch to see which routines are used
// (comment me out in production)
#define LAPACK_DEBUG

#ifdef LAPACK_DEBUG
#include <iostream>  // For debug

#define LAPACK_DEBUG_LOG std::cerr << __PRETTY_FUNCTION__ << std::endl;

#else

#define LAPACK_DEBUG_LOG

#endif

namespace LinearAlgebra::Lapack
{
  // SGELS Least squares |A.x-b|_2 or |A^t.x-b|_2
  //================================================================
  // CAVEAT: inplace!
  //
  static inline lapack_int
  gels(const Lapack_Order_Enum matrix_layout,
       const Lapack_Transpose_Enum trans,
       lapack_int m,
       lapack_int n,
       lapack_int nrhs,
       float* a,
       lapack_int lda,
       float* b,
       lapack_int ldb)
  {
    return LAPACKE_sgels(matrix_layout, trans, m, n, nrhs, a, lda, b, ldb);
  }
  static inline lapack_int
  gels(const Lapack_Order_Enum matrix_layout,
       const Lapack_Transpose_Enum trans,
       lapack_int m,
       lapack_int n,
       lapack_int nrhs,
       double* a,
       lapack_int lda,
       double* b,
       lapack_int ldb)
  {
    return LAPACKE_dgels(matrix_layout, trans, m, n, nrhs, a, lda, b, ldb);
  }

  static inline lapack_int
  gels(const Lapack_Order_Enum matrix_layout,
       const Lapack_Transpose_Enum trans,
       lapack_int m,
       lapack_int n,
       lapack_int nrhs,
       std::complex<float>* a,
       lapack_int lda,
       std::complex<float>* b,
       lapack_int ldb)
  {
    return LAPACKE_cgels(matrix_layout, trans, m, n, nrhs, a, lda, b, ldb);
  }
  static inline lapack_int
  gels(const Lapack_Order_Enum matrix_layout,
       const Lapack_Transpose_Enum trans,
       lapack_int m,
       lapack_int n,
       lapack_int nrhs,
       std::complex<double>* a,
       lapack_int lda,
       std::complex<double>* b,
       lapack_int ldb)
  {
    return LAPACKE_zgels(matrix_layout, trans, m, n, nrhs, a, lda, b, ldb);
  }
  
  // potrf L.L^H or U^H.U Cholesky Factorization
  //================================================================
  //
  static inline lapack_int
  potrf(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        float* a,
        const std::size_t lda)
  {
    return LAPACKE_spotrf2(matrix_layout, uplo, n, a, lda);
  }
  static inline lapack_int
  potrf(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        double* a,
        const std::size_t lda)
  {
    return LAPACKE_dpotrf2(matrix_layout, uplo, n, a, lda);
  }
  static inline lapack_int
  potrf(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        std::complex<float>* a,
        const std::size_t lda)
  {
    return LAPACKE_cpotrf2(matrix_layout, uplo, n, a, lda);
  }
  static inline lapack_int
  potrf(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        std::complex<double>* a,
        const std::size_t lda)
  {
    return LAPACKE_zpotrf2(matrix_layout, uplo, n, a, lda);
  }

  // potrs solve linear system from portf result
  //
  // CAVEAT: if rhs is a vector, its increment must be = 1 (otherwise
  //         a copy is mandatory)
  //
  //================================================================
  //

  static inline lapack_int
  potrs(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        const std::size_t nrhs,
        float* a,
        const std::size_t lda,
        float* b,
        const std::size_t ldb)
  {
    return LAPACKE_spotrs(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }
  
  static inline lapack_int
  potrs(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        const std::size_t nrhs,
        double* a,
        const std::size_t lda,
        double* b,
        const std::size_t ldb)
  {
    return LAPACKE_dpotrs(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }

  static inline lapack_int
  potrs(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        const std::size_t nrhs,
        std::complex<float>* a,
        const std::size_t lda,
        std::complex<float>* b,
        const std::size_t ldb)
  {
    return LAPACKE_cpotrs(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }

  static inline lapack_int
  potrs(const Lapack_Order_Enum matrix_layout,
        const Lapack_UpLo_Enum uplo,
        const std::size_t n,
        const std::size_t nrhs,
        std::complex<double>* a,
        const std::size_t lda,
        std::complex<double>* b,
        const std::size_t ldb)
  {
    return LAPACKE_zpotrs(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }

  //
  // DRIVER routines
  //
  // posv solves linear system (compared to potrs also perform
  // iterative refinement etc...)
  //
  // CAVEAT: if rhs is a vector, its increment must be = 1 (otherwise
  //         a copy is mandatory)
  //
  //================================================================
  //
  static inline lapack_int
  posv(const Lapack_Order_Enum matrix_layout,
       const Lapack_UpLo_Enum uplo,
       const std::size_t n,
       const std::size_t nrhs,
       float* a,
       const std::size_t lda,
       float* b,
       const std::size_t ldb)
  {
    return LAPACKE_sposv(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }
  static inline lapack_int
  posv(const Lapack_Order_Enum matrix_layout,
       const Lapack_UpLo_Enum uplo,
       const std::size_t n,
       const std::size_t nrhs,
       double* a,
       const std::size_t lda,
       double* b,
       const std::size_t ldb)
  {
    return LAPACKE_dposv(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }

  static inline lapack_int
  posv(const Lapack_Order_Enum matrix_layout,
       const Lapack_UpLo_Enum uplo,
       const std::size_t n,
       const std::size_t nrhs,
       std::complex<float>* a,
       const std::size_t lda,
       std::complex<float>* b,
       const std::size_t ldb)
  {
    return LAPACKE_cposv(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }

  static inline lapack_int
  posv(const Lapack_Order_Enum matrix_layout,
       const Lapack_UpLo_Enum uplo,
       const std::size_t n,
       const std::size_t nrhs,
       std::complex<double>* a,
       const std::size_t lda,
       std::complex<double>* b,
       const std::size_t ldb)
  {
    return LAPACKE_zposv(matrix_layout, uplo, n, nrhs, a, lda, b, ldb);
  }
}  // namespace LinearAlgebra::Lapack
