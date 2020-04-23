#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/matrix_fwd.hpp"
#include "LinearAlgebra/lapack/subroutines.hpp"
#include "LinearAlgebra/lapack/to_lapack_uplo.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include "LinearAlgebra/utils/sfinae_vmt_helpers.hpp"

#include <gtest/gtest.h>

namespace LinearAlgebra
{
  template <typename MA_IMPL, typename MB_IMPL>
  auto
  posv(Dense_Matrix_Crtp<MA_IMPL>& A, Dense_Matrix_Crtp<MB_IMPL>& B) -> std::enable_if_t<
      //
      // CAVEAT: check if we can use potentially use an incomplete
      //         type Lapack::To_Lapack_UpLo_v<MA_IMPL> instead of
      //         Lapack::Lapack_UpLo_Enum::Low in a SFINEA context.
      //
      Always_True_v<decltype(Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,  //
                                          Lapack::Lapack_UpLo_Enum::Low,            // <- here
                                          A.I_size(),                               //
                                          B.J_size(),                               //
                                          A.data(),                                 //
                                          A.leading_dimension(),                    //
                                          B.data(),                                 //
                                          B.leading_dimension()))>                  //
                                                                                    //
          and
          //
          (Is_Symmetric_Matrix_v<MA_IMPL> or Is_Hermitian_Matrix_v<MA_IMPL>)
          //
          and
          //
          Is_Full_Matrix_v<MB_IMPL>,
      //
      lapack_int>
  {
    return Lapack::posv(Lapack::Lapack_Order_Enum::Column_Major,
                        Lapack::To_Lapack_UpLo_v<MA_IMPL>,
                        A.I_size(),
                        B.J_size(),
                        A.data(),
                        A.leading_dimension(),
                        B.data(),
                        B.leading_dimension());
  }
}

using namespace LinearAlgebra;
using namespace LinearAlgebra::Lapack;

TEST(Posv, sfinae)
{
  Matrix<double> A(5, 5);
  Tiny_Symmetric_Matrix<double, 5> B;

  posv(B, A);

  EXPECT_FALSE(Is_Symmetric_Matrix_v<Vector<double>>);
}
