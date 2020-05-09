#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include <type_traits>
#include "LinearAlgebra/dense/vector_fwd.hpp"

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

//----------------------------------------------------------------
TEST(Vector, construction_mixed_type_1)
{
  Vector<int> v(3);
  v = 1;
  Tiny_Vector<double, 3> w(v);
  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 1);
  EXPECT_EQ(w[2], 1);

  // Check that we really perform a copy
  v[1] = 2;
  EXPECT_EQ(w[1], 1);
}
TEST(Vector, construction_mixed_type_2)
{
  Tiny_Vector<double, 3> v;
  v = 1;
  Vector<int> w(v);
  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 1);
  EXPECT_EQ(w[2], 1);

  // Check that we really perform a copy
  v[1] = 2;
  EXPECT_EQ(w[1], 1);
}
TEST(Vector, construction_mixed_type_3)
{
  Vector<double> v(3);
  v = 1;
  Vector<int> w(v.as_generic_view());
  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 1);
  EXPECT_EQ(w[2], 1);

  // Check that we really perform a copy
  v[1] = 2;
  EXPECT_EQ(w[1], 1);
}
//----------------------------------------------------------------
TEST(Vector, extended_constructor_for_static_size)
{
  Tiny_Vector<int, 3> v(3);
  EXPECT_EQ(v.size(), 3);
}
TEST(Vector, extended_constructor_for_static_size_check)
{
  EXPECT_DEBUG_DEATH((Tiny_Vector<int, 3>(4)), "");
}
//----------------------------------------------------------------
TEST(Vector, constructor_raw_pointer)
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

TEST(Vector, view_constness)
{
  int data[] = {1, 2, 3, 4, 5};

  Default_Vector_View<int, std::integral_constant<size_t, 3>, std::integral_constant<size_t, 2>> v(
      data);

  EXPECT_FALSE(std::is_const_v<std::remove_const_t<decltype(v[0])>>);

  // Note: even if not a "Const_view", you cannot modify const view:
  //
  // Note: you cannot declare const Default_Vector_View<const int,...> to mimic "const double *const"
  //
  //       this would have been ideal, however this leads to tricky
  //       implementation problems (we have chosen a simpler design
  //       with only one "const" which is less versatile but simpler
  //       to implement)
  //
  const Default_Vector_View<int,
                            std::integral_constant<size_t, 3>,
                            std::integral_constant<size_t, 2>>
      c_v(data);

  EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(c_v[0])>>);

  Default_Vector_Const_View<int,
                            std::integral_constant<size_t, 3>,
                            std::integral_constant<size_t, 2>>
      c_cv(data);

  EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(c_cv[0])>>);
}

TEST(Vector, view_empty_constructor)
{
  Generic_Vector_Const_View<int> V1;
  Generic_Vector_View<int> V2;
  Default_Vector_View<int,
                      std::integral_constant<std::size_t, 4>,
                      std::integral_constant<std::size_t, 4>>
      V3;

  EXPECT_TRUE(V1.data() == nullptr);
  EXPECT_TRUE(V2.data() == nullptr);
  EXPECT_TRUE(V3.data() == nullptr);
}

TEST(Vector, view_empty_constructor_debug_death)
{
  Default_Vector_View<int,
                      std::integral_constant<std::size_t, 4>,
                      std::integral_constant<std::size_t, 4>>
      V;

  EXPECT_DEBUG_DEATH(V[0], "");
}
