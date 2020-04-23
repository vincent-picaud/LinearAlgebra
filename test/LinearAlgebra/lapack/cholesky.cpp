#include "LinearAlgebra/lapack/lapack.hpp"

#include "LinearAlgebra/matrix.hpp"

#include "LinearAlgebra/scalar_functions/dist_2_vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Lapack, potrf)
{
  const size_t n = 5;

  Vector<double> v(n), w(n);
  v = 1;
  Symmetric_Matrix<double> M(n, n);

  M                                     = 0;
  create_vector_view_matrix_diagonal(M) = 10;
  M(4, 0)                               = 5;

  w = M * v;

  // L*LT
  int info = Lapack::potrf(Lapack::Lapack_Order_Enum::Column_Major,
                           Lapack::Lapack_UpLo_Enum::Low,
                           M.I_size(),
                           M.data(),
                           M.leading_dimension());

  // also see potrs
  auto L = create_matrix_view_lower_triangular(M.as_const());

  w = inverse(L) * w;
  w = inverse(transpose(L)) * w;

  EXPECT_DOUBLE_EQ(1 + dist_2(v, w), 1);
}
