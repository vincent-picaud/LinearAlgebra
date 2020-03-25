#include "LinearAlgebra/utils/crtp.hpp"

#include <gtest/gtest.h>

namespace LinearAlgebra
{
  struct A final : Crtp<A>
  {
  };
}

using namespace LinearAlgebra;

TEST(Crtp, trivial)
{
  EXPECT_TRUE((std::is_trivial_v<A>));
  EXPECT_TRUE((Is_Crtp_Interface_Of_v<Crtp, A>));
}
