#include "LinearAlgebra/scalar_functions/norm_2_vector.hpp"

#include "LinearAlgebra/dense/vector_header.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(norm_2, vector_blas)
{
  Vector<double> V(5);
  V = 2;
  DEBUG_RESET_SELECTED();
  ASSERT_DOUBLE_EQ(norm_2(V), std::sqrt(5 * 4));
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
                  (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));

  DEBUG_RESET_SELECTED();
  ASSERT_DOUBLE_EQ(squared_norm_2(V), 5 * 4);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
                  (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));
}

TEST(norm_2, vector_blas_complex)
{
  Vector<std::complex<float>> V(5);
  V = std::complex<float>(0, 2);

  DEBUG_RESET_SELECTED();

  ASSERT_FLOAT_EQ(norm_2(V), std::sqrt(5 * 4));
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
                  (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));

  DEBUG_RESET_SELECTED();
  ASSERT_FLOAT_EQ(squared_norm_2(V), 5 * 4);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
                  (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));
}

TEST(norm_2, vector_generic)
{
  // CAVEAT we return double for norm, even if integer components
  Vector<int> V(5);
  V = 2;
  DEBUG_RESET_SELECTED();
  ASSERT_DOUBLE_EQ(norm_2(V), std::sqrt(5 * 4));
  EXPECT_TRUE((std::is_same_v<double, decltype(norm_2(V))>));
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  DEBUG_RESET_SELECTED();
  ASSERT_DOUBLE_EQ(squared_norm_2(V), 5 * 4);
  EXPECT_TRUE((std::is_same_v<double, decltype(norm_2(V))>));
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);
}
