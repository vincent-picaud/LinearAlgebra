#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Tiny_Vector, Constructor)
{
  Tiny_Vector<int, 3> v;

  EXPECT_EQ(v.size(), 3);

  v[2] = 2;
  EXPECT_EQ(v[2], 2);
}
TEST(Vector, Constructor)
{
  Vector<int> v(3);

  EXPECT_EQ(v.size(), 3);

  v[2] = 2;
  EXPECT_EQ(v[2], 2);
}

TEST(Tiny_Vector_View, Constructor)
{
  int data[] = {1, 2, 3, 4, 5};

  // Construction from the raw type
  Default_Vector_View<int, std::integral_constant<size_t, 3>, std::integral_constant<size_t, 2>> v(
      data);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
  EXPECT_EQ(v[2], 5);

  v[1] = 10;
  EXPECT_EQ(data[2], 10);
}

TEST(Tiny_Vector_Const_View, Constructor)
{
  int data[] = {1, 2, 3, 4, 5};

  // Construction from the raw type
  Default_Vector_View<int, size_t, size_t> v(data, 3, 2);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
  EXPECT_EQ(v[2], 5);

  // A more user friendly alias
  Tiny_Vector_View<int, 5> v_user(data);

  EXPECT_EQ(v_user[2], 3);
  v[1] = 10;
  EXPECT_EQ(v_user[2], 10);
}
