#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix, Static)
{
  Tiny_Matrix<int, 3, 2> m;

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  m(2, 1) = 10;
  EXPECT_EQ(m(2, 1), 10);
}

TEST(Matrix, Dynamic)
{
  Matrix<int> m(3, 2);

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  m(2, 1) = 10;
  EXPECT_EQ(m(2, 1), 10);
}

TEST(Matrix, weird_type)
{
  Default_Matrix<int, Matrix_Special_Structure_Enum::None, Matrix_Storage_Mask_Enum::None, size_t,
                 std::integral_constant<size_t, 2>, std::integral_constant<size_t, 5>>
      m(3, std::integral_constant<size_t, 2>(), std::integral_constant<size_t, 5>());

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  m(2, 1) = 10;
  EXPECT_EQ(m(2, 1), 10);
}

TEST(Matrix, Static_View)
{
  int d[10];

  Tiny_Matrix_View<int, 3, 2> m(d);

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  m(0, 0) = 1;
  m(1, 0) = 2;
  m(2, 0) = 3;
  m(0, 1) = 4;
  m(1, 1) = 5;
  m(2, 1) = 6;

  EXPECT_EQ(d[0], 1);
  EXPECT_EQ(d[1], 2);
  EXPECT_EQ(d[2], 3);
  EXPECT_EQ(d[3], 4);
  EXPECT_EQ(d[4], 5);
  EXPECT_EQ(d[5], 6);
}
TEST(Matrix, Empty_View)
{
  Matrix_View<int> m(nullptr);

  EXPECT_EQ(m.I_size(), 0);
  EXPECT_EQ(m.J_size(), 0);
}
TEST(Matrix, Empty_Const_View)
{
  Matrix_Const_View<int> m(nullptr);

  EXPECT_EQ(m.I_size(), 0);
  EXPECT_EQ(m.J_size(), 0);
}

TEST(Tiny_Matrix_View, Constructor)
{
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  Tiny_Symmetric_Matrix_View<int, 3, 3> v(data);

  EXPECT_EQ(v.I_size(), 3);
}

// TEST(Tiny_Matrix_Const_View, Constructor)
// {
//   int data[] = {1, 2, 3, 4, 5};

//   Tiny_Matrix_Const_View<int, 3, 2> v(data);

//   EXPECT_EQ(v.size(), 3);
//   EXPECT_EQ(v[0], 1);
//   EXPECT_EQ(v[1], 3);
//   EXPECT_EQ(v[2], 5);

//   // Should trigger compile time error
//   //  v[1] = 10;
//   // EXPECT_EQ(data[2], 10);
// }
