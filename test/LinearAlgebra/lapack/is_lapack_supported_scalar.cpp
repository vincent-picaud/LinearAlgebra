#include "LinearAlgebra/lapack/is_lapack_supported_scalar.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra::Lapack;

TEST(Is_Lapack_Supported_Scalar, demo)
{
  EXPECT_FALSE((Is_Lapack_Supported_Scalar_v<int>));
  EXPECT_TRUE((Is_Lapack_Supported_Scalar_v<double>));
  EXPECT_TRUE((Is_Lapack_Supported_Scalar_v<std::complex<float>>));
}
