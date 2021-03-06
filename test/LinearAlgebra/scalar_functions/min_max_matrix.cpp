#include "LinearAlgebra/scalar_functions/min_max_matrix.hpp"
//
// keep include split apart to check them!
//
#include "LinearAlgebra/matrix.hpp"
//
#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(min_max, empty_matrix)
{
  Tiny_Matrix<int, 0, 0> v;

  EXPECT_EQ(min(v), std::numeric_limits<int>::max());
  EXPECT_EQ(max(v), std::numeric_limits<int>::min());
}

TEST(min_max, basic_matrix)
{
  auto m_1 = create_matrix({{1, 2, 3}, {4, 5, 6}});
  EXPECT_EQ(min(m_1), 1);
  EXPECT_EQ(max(m_1), 6);
}
