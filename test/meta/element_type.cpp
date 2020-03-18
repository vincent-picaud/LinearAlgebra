#include "LinearAlgebra/meta/element_type.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <ccomplex>

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Element_Type, basic)
{
  Tiny_Vector<double, 3> dV;
  Tiny_Vector<std::complex<double>, 3> zV;

  EXPECT_TRUE((std::is_same_v<double, Element_Type_t<decltype(dV)>>));
  EXPECT_TRUE(
      (std::is_same_v<std::complex<double>, Common_Element_Type_t<decltype(dV), decltype(zV), decltype(dV)>>));
}
