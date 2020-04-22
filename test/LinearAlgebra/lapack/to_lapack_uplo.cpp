#include "LinearAlgebra/lapack/to_lapack_uplo.hpp"

#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;
using namespace LinearAlgebra::Lapack;

TEST(To_Lapack_UpLo, demo)
{
  EXPECT_EQ(To_Lapack_UpLo_v<Symmetric_Matrix<double>::matrix_storage_mask_type::value>,
            Lapack_UpLo_Enum::Low);
}
