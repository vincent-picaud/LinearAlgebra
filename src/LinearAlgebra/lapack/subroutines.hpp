#pragma once

#include "LinearAlgebra/lapack/lapack_config.hpp"

#if !(HAS_LAPACK)
#error
#endif

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
  // TODO to move else where
  enum Lapack_Order_Enum : int
  {
    Row_Major    = LAPACK_ROW_MAJOR,
    Column_Major = LAPACK_COL_MAJOR
  };

  enum Lapack_UpLo_Enum : char
  {
    Up  = 'U',
    Low = 'L'
  };

  // potrf (Cholesky)
  //================================================================
  //
  lapack_int
  potrf(const Lapack_Order_Enum matrix_layout, const Lapack_UpLo_Enum uplo, const std::size_t n,
        float* a, const std::size_t lda)
  {
    return LAPACKE_spotrf2(matrix_layout, uplo, n, a, lda);
  }
  lapack_int
  potrf(const Lapack_Order_Enum matrix_layout, const Lapack_UpLo_Enum uplo, const std::size_t n,
        double* a, const std::size_t lda)
  {
    return LAPACKE_dpotrf2(matrix_layout, uplo, n, a, lda);
  }
  lapack_int
  potrf(const Lapack_Order_Enum matrix_layout, const Lapack_UpLo_Enum uplo, const std::size_t n,
        std::complex<float>* a, const std::size_t lda)
  {
    return LAPACKE_cpotrf2(matrix_layout, uplo, n, a, lda);
  }
  lapack_int
  potrf(const Lapack_Order_Enum matrix_layout, const Lapack_UpLo_Enum uplo, const std::size_t n,
        std::complex<double>* a, const std::size_t lda)
  {
    return LAPACKE_zpotrf2(matrix_layout, uplo, n, a, lda);
  }
}
