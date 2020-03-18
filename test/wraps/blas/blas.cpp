#include "LinearAlgebra/wraps/blas/blas.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

#if (HAS_BLAS)

TEST(Blas, demo) { ASSERT_TRUE(HAS_BLAS); }

#endif
