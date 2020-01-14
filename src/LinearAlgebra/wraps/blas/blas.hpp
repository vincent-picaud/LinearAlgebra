#pragma once

#include "LinearAlgebra/wraps/blas/blas_config.hpp"

#include <cstddef>

#include <iostream> // For debug

namespace LinearAlgebra
{
  namespace Blas
  {
    /////////////
    // Level 1 //
    /////////////

    void
    copy(const std::size_t n, const float *x, const std::size_t incx, float *y,
         const std::size_t incy)
    {
      std::cerr << __PRETTY_FUNCTION__ << std::endl;
      
      cblas_scopy(n, x, incx, y, incy);
    }
  }

}
