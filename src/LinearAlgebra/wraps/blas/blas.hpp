#pragma once

#include "LinearAlgebra/wraps/blas/blas_config.hpp"

#if (HAS_BLAS)

#include <ccomplex>
#include <cstddef>

#include <iostream>  // For debug

namespace LinearAlgebra
{
  namespace Blas
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
      std::cerr << __PRETTY_FUNCTION__ << std::endl;

      cblas_scopy(n, x, incx, y, incy);
    }

    void
    copy(const std::size_t n, const double *x, const std::size_t incx, double *y,
         const std::size_t incy)
    {
      std::cerr << __PRETTY_FUNCTION__ << std::endl;

      cblas_dcopy(n, x, incx, y, incy);
    }

    void
    copy(const std::size_t n, const std::complex<float> *x, const std::size_t incx,
         std::complex<float> *y, const std::size_t incy)
    {
      std::cerr << __PRETTY_FUNCTION__ << std::endl;

      cblas_ccopy(n, x, incx, y, incy);
    }

    void
    copy(const std::size_t n, const std::complex<double> *x, const std::size_t incx,
         std::complex<double> *y, const std::size_t incy)
    {
      std::cerr << __PRETTY_FUNCTION__ << std::endl;

      cblas_zcopy(n, x, incx, y, incy);
    }
  }

}

#endif  // HAS_BLAS
