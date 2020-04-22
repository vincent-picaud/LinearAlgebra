// Role: main lapack header
//
#pragma once

// Load automatically generated configuration file
//
#include "LinearAlgebra/lapack/lapack_config.hpp"

// If we have lapack installed include the remaining file
//
#if (HAS_LAPACK)

#include "LinearAlgebra/lapack/lapack_enum.hpp"
#include "LinearAlgebra/lapack/is_lapack_supported_scalar.hpp"
#include "LinearAlgebra/lapack/to_lapack_uplo.hpp"
#include "LinearAlgebra/lapack/subroutines.hpp"

#endif
