#include "LinearAlgebra/scalar_functions/dist_2_vector.hpp"

#include "LinearAlgebra/scalar_functions/dot_vector.hpp"
#include "LinearAlgebra/scalar_functions/norm_2_vector.hpp"

#include "LinearAlgebra/dense/vector_header.hpp"

#include <ccomplex>

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(dist_2, vector_complex)
{
  Vector<std::complex<float>> V1(5);
  V1 = std::complex<float>(1, 2);
  Vector<std::complex<float>> V2(5);
  V2 = std::complex<float>(1, 4);

  DEBUG_RESET_SELECTED();

  ASSERT_FLOAT_EQ(dist_2(V1, V2), std::sqrt(5 * 4));
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  DEBUG_RESET_SELECTED();
  ASSERT_FLOAT_EQ(squared_dist_2(V1, V2), 5 * 4);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);
}

TEST(dist_2, vector_dot_norm_dist)
{
  Vector<std::complex<float>> V1(5);
  V1 = std::complex<float>(3, 2);

  ASSERT_FLOAT_EQ(dist_2(V1, V1), 0);
  auto Z = dot(V1, V1);

  ASSERT_FLOAT_EQ(0, std::imag(Z));
  ASSERT_FLOAT_EQ(squared_norm_2(V1), std::real(Z));
}
