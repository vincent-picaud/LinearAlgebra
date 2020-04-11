#include "LinearAlgebra/utils/crtp.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

namespace LinearAlgebra
{
  struct A final : Crtp<A>
  {
  };
}

namespace LinearAlgebra
{
}

using namespace LinearAlgebra;

TEST(Crtp, trivial)
{
  EXPECT_TRUE((std::is_trivial_v<A>));
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Crtp, A>));
}

TEST(Crtp, variadic_Is_Crtp_Interface_Of_v)
{
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Crtp, A>));
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Crtp, A, A>));
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Crtp, A, A, A>));
  EXPECT_FALSE((Is_Crtp_Interface_Of_v<Crtp, A, double, A>));
  EXPECT_FALSE((Is_Crtp_Interface_Of_v<Dense_Vector_Crtp, A, A, A>));
  EXPECT_FALSE((Is_Crtp_Interface_Of_v<Dense_Vector_Crtp, A, double, A>));
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Dense_Vector_Crtp, Tiny_Vector<int, 3>>));
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Dense_Vector_Crtp, Tiny_Vector<int, 3>, Vector<double>>));
  EXPECT_FALSE(
      (Is_Crtp_Interface_Of_v<Dense_Vector_Crtp, Tiny_Vector<int, 3>, double, Vector<double>>));
}
