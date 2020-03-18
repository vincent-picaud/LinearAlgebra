// Role: main blas header
//
#pragma once

#include "LinearAlgebra/wraps/blas/blas_config.hpp"

#if (HAS_BLAS)
#include "LinearAlgebra/wraps/blas/subroutines.hpp"
#include "LinearAlgebra/wraps/blas/to_cblas_transpose.hpp"
#include "LinearAlgebra/wraps/blas/is_cblas_supported_scalar.hpp"
#endif

