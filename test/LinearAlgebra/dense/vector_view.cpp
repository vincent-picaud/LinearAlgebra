#include "LinearAlgebra/dense/vector_view.hpp"
#include "LinearAlgebra/expr/vector_expr.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_View, dynamic_of_static)
{
  Tiny_Vector<int, 10> v;
  v = 1;

  auto view_v = create_vector_view(v, 1, 3);
  view_v      = 2;

  EXPECT_TRUE((std::is_same_v<std::size_t, typename decltype(view_v)::size_type>));
  EXPECT_EQ(view_v.size(), 2);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 1);
}

TEST(Vector_View, static_of_static)
{
  Tiny_Vector<int, 10> v;
  v           = 1;
  auto view_v = create_vector_view(v, std::integral_constant<std::size_t, 1>(),
                                   std::integral_constant<std::size_t, 3>());
  view_v      = 2;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 2>,
                              typename decltype(view_v)::size_type>));
  EXPECT_EQ(view_v.size(), 2);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 1);
}

TEST(Vector_View, static_of_dynamic)
{
  Vector<int> v(10);
  v           = 1;
  auto view_v = create_vector_view(v, std::integral_constant<std::size_t, 1>(),
                                   std::integral_constant<std::size_t, 3>());
  view_v      = 2;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 2>,
                              typename decltype(view_v)::size_type>));
  EXPECT_EQ(view_v.size(), 2);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 1);
}

TEST(Vector_View, static_of_dynamic_with_stride)
{
  Default_Vector<int, std::size_t, std::integral_constant<std::size_t, 5>> v(10);

  v           = 1;
  auto view_v = create_vector_view(v, std::integral_constant<std::size_t, 1>(),
                                   std::integral_constant<std::size_t, 3>());
  view_v      = 2;

  EXPECT_TRUE((std::is_same_v<std::integral_constant<std::size_t, 2>,
                              typename decltype(view_v)::size_type>));
  EXPECT_EQ(view_v.size(), 2);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 1);
}

TEST(Vector_View, constness_check)
{
  Tiny_Vector<int, 10> v;
  v           = 1;
  v[1]        = 2;
  auto view_v = create_vector_view(v.as_const(), 1, 3);

  EXPECT_TRUE((std::is_same_v<std::size_t, typename decltype(view_v)::size_type>));
  EXPECT_EQ(view_v.size(), 2);

  EXPECT_EQ(view_v[0], 2);
  EXPECT_EQ(view_v[1], 1);
}

TEST(Vector_View, from_vector_to_view)
{
  Tiny_Vector<int, 3> v;
  v[2] = 10;

  auto view = create_vector_view(v);
  view[2]   = 1;
  EXPECT_EQ(v[2], 1);
  EXPECT_TRUE((std::is_same_v<std::integral_constant<size_t, 3>, decltype(view.size())>));
}
