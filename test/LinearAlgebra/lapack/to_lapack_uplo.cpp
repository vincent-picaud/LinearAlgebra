#include "LinearAlgebra/lapack/to_lapack_uplo.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/utils/is_complete.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;
using namespace LinearAlgebra::Lapack;

TEST(To_Lapack_UpLo, demo)
{
  EXPECT_EQ(To_Lapack_UpLo_v<Symmetric_Matrix<double>::matrix_storage_mask_type>,
            Lapack_UpLo_Enum::Low);

  // EXPECT_EQ(To_Lapack_UpLo_v<Symmetric_Matrix<double>>, Lapack_UpLo_Enum::Low);

  // CAVEAT: if you want to test complete/incomplete do NOT use "_v"
  // !!! By example,
  //
  // EXPECT_FALSE((Is_Complete_v<To_Lapack_UpLo_v<Symmetric_Matrix<double>>>));
  //
  // Does NOT work
  //
  EXPECT_TRUE((Is_Complete_v<To_Lapack_UpLo<Symmetric_Matrix<double>>>));
  EXPECT_FALSE(
      (Is_Complete_v<To_Lapack_UpLo<Matrix<double>>>));  // For full matri no up/lo is defined
}
