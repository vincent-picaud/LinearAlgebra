
#include "LinearAlgebra/scalar_functions/dot.hpp"

#include "LinearAlgebra/dense/vector_header.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(dot, vector_dim)
{
  Vector<int> V1(10);
  Vector<double> V2(5);

  EXPECT_DEBUG_DEATH(dot(V1, V2), "");
}

TEST(dot, vector_1)
{
  Vector<int> V1(5);
  Vector<double> V2(5);

  V1 = 2;
  V2 = 3;

  EXPECT_EQ(dot(V1, V2), 5 * 2 * 3);
}

TEST(dot, vector_2)
{
  Vector<std::complex<int>> V1(5);
  Vector<double> V2(5);

  V1 = std::complex<int>(0, 2);
  V2 = 3;

  EXPECT_TRUE((std::is_same_v<std::complex<int>, decltype(dot(V1, V2))>));
  // CAVEAT: because of the way C++ works:
  //         std::common_type<std::complex<int>,double> is
  //         std::complex<int> and not std::complex<double>
  EXPECT_EQ(dot(V1, V2), std::complex<int>(0, -5 * 2 * 3));
}
