#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <ccomplex>

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Operator_Overloading, scalar_product_vmt)
{
  Tiny_Vector<double, 5> V;
  V = 2;

  V = 4 * V;

  EXPECT_DOUBLE_EQ(V[2], 8);
}

// Case complex<T> * V<T>
//
TEST(Operator_Overloading, complex_1_scalar_product_vmt)
{
  Tiny_Vector<std::complex<double>, 5> V;
  Tiny_Vector<double, 5> W;
  W = 2;

  V = std::complex<double>(4) * W;

  EXPECT_DOUBLE_EQ(V[2].real(), 8);
  EXPECT_DOUBLE_EQ(V[2].imag(), 0);
}

// Case T * V<complex<T>>
//
TEST(Operator_Overloading, complex_2_scalar_product_vmt)
{
  Tiny_Vector<std::complex<double>, 5> V;
  Tiny_Vector<std::complex<double>, 5> W;
  W = 2;

  V = 4 * W;

  EXPECT_DOUBLE_EQ(V[2].real(), 8);
  EXPECT_DOUBLE_EQ(V[2].imag(), 0);
}
