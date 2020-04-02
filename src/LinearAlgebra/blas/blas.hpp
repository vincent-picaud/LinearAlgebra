// Role: main blas header
//
#pragma once

#include "LinearAlgebra/blas/blas_config.hpp"

#if (HAS_BLAS)
#include "LinearAlgebra/blas/subroutines.hpp"
#include "LinearAlgebra/blas/to_cblas_transpose.hpp"
#include "LinearAlgebra/blas/to_cblas_uplo.hpp"
#include "LinearAlgebra/blas/to_cblas_diag.hpp"
#include "LinearAlgebra/blas/is_cblas_supported_scalar.hpp"
#endif

