#include "LinearAlgebra/scalar_functions/norm_inf_vector.hpp"

#include "LinearAlgebra/dense/vector_header.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(norm_inf, vector_blas)
{
  Vector<double> V(5);
  V = 2;
  DEBUG_RESET_SELECTED();
  ASSERT_DOUBLE_EQ(norm_inf(V), 2);

  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  // DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
  //                 (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));
}

TEST(norm_inf, vector_blas_complex)
{
  Vector<std::complex<float>> V(5);
  V = std::complex<float>(0, -2);

  DEBUG_RESET_SELECTED();

  ASSERT_FLOAT_EQ(norm_inf(V), 2);

  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Generic);

  // DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(),
  //                (HAS_BLAS ? Expr_Selector_Enum::Blas : Expr_Selector_Enum::Generic));
}
