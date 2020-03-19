#include "LinearAlgebra/dense/matrix_map.hpp"
#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_Map, basic)
{
  Tiny_Matrix<int, 3, 2> mat;

  mat(0, 0) = 1;
  mat(2, 1) = 2;

  auto mat_dest = map([](const auto mat_i) { return (double)mat_i + 1; }, mat);

  EXPECT_EQ(mat(0, 0), 1);
  EXPECT_EQ(mat(2, 1), 2);

  EXPECT_EQ(mat_dest(0, 0), 2);
  EXPECT_EQ(mat_dest(2, 1), 3);

  EXPECT_EQ(mat_dest.I_size(), 3);
  EXPECT_EQ(mat_dest.J_size(), 2);

  EXPECT_TRUE((std::is_same_v<typename decltype(mat_dest)::I_size_type,
                              std::integral_constant<std::size_t, 3>>));
  EXPECT_TRUE((std::is_same_v<typename decltype(mat_dest)::J_size_type,
                              std::integral_constant<std::size_t, 2>>));
  EXPECT_TRUE((std::is_same_v<typename decltype(mat)::element_type, int>));
  EXPECT_TRUE((std::is_same_v<typename decltype(mat_dest)::element_type, double>));
}
