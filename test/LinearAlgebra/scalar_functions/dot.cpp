
#include "LinearAlgebra/scalar_functions/dot.hpp"

#include "LinearAlgebra/dense/vector_header.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(dot, vector_dim)
{
  Vector<int> V1(10);
  Vector<double> V2(5);

  EXPECT_DEBUG_DEATH(dot(V1,V2),"");
}

