#include "LinearAlgebra/wraps/blas/blas.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Blas, demo)
{
  ASSERT_TRUE(HAS_BLAS);
}
