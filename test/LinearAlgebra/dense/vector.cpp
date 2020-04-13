#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector, is_trivially_copyable)
{
  using tiny_vector_type = Tiny_Vector<int, 3>;

  // FALSE as we have redefine custom move operator...
  EXPECT_FALSE((std::is_trivially_copyable_v<tiny_vector_type>));

  using vector_type = Vector<int>;

  EXPECT_FALSE((std::is_trivially_copyable_v<vector_type>));
}

TEST(Vector, constructor_static)
{
  Tiny_Vector<int, 3> v;

  EXPECT_EQ(v.size(), 3);

  v[2] = 2;
  EXPECT_EQ(v[2], 2);
}
TEST(Vector, constructor_dynamic)
{
  Vector<int> v(3);

  EXPECT_EQ(v.size(), 3);

  v[2] = 2;
  EXPECT_EQ(v[2], 2);
}

TEST(Vector_View, constructor_raw_pointer)
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

// TEST(Vector_Const_View, Constructor)
// {
//   int data[] = {1, 2, 3, 4, 5};

//   // Construction from the raw type
//   Default_Vector_View<int, size_t, size_t> v(data, 3, 2);

//   EXPECT_EQ(v.size(), 3);
//   EXPECT_EQ(v[0], 1);
//   EXPECT_EQ(v[1], 3);
//   EXPECT_EQ(v[2], 5);

//   // A more user friendly alias
//   Tiny_Vector_View<int, 5> v_user(data);

//   EXPECT_EQ(v_user[2], 3);
//   v[1] = 10;
//   EXPECT_EQ(v_user[2], 10);
// }
