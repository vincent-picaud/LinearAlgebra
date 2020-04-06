#include "LinearAlgebra/utils/element_type.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <ccomplex>

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Element_Type, basic)
{
  Tiny_Vector<double, 3> dV;
  Tiny_Vector<std::complex<double>, 3> zV;

  EXPECT_TRUE((std::is_same_v<double, Element_Type_t<decltype(dV)>>));
  EXPECT_TRUE((std::is_same_v<std::complex<double>,
                              Common_Element_Type_t<decltype(dV), decltype(zV), decltype(dV)>>));
}

template <typename T>
struct A
{
  using element_type = T;
};

TEST(Element_Type, common_element_type)
{
  Tiny_Vector<double, 3> dV;
  Tiny_Vector<std::complex<double>, 3> zV;

  EXPECT_TRUE((std::is_same_v<double, Common_Element_Type_t<A<int>, A<double>>>));
  EXPECT_TRUE((std::is_same_v<double, Common_Element_Type_t<A<double>, A<int>>>));
  EXPECT_TRUE((std::is_same_v<double, Common_Element_Type_t<A<float>, A<double>, A<int>>>));
  EXPECT_TRUE((std::is_same_v<std::complex<float>,
                              Common_Element_Type_t<A<std::complex<float>>, A<double>, A<int>>>));

  EXPECT_TRUE(
      (std::is_same_v<std::complex<int>,  // CAVEAT: unfortunately this is not std::complex<float>
                      Common_Element_Type_t<A<std::complex<int>>, A<float>, A<int>>>));
}
