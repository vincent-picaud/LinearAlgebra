#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(MetaExpr_Crtp, basic_1)
{
  const size_t n = 4;
  int data[n]={1,2,3,4};

  auto V1 = create_vector_view(data,n);

  Vector<double> V2(n);

  //  V2=V2+4*V1;
}
