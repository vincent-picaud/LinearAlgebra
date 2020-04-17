#include "LinearAlgebra/dense/vector_create_generic_view.hpp"

#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Vector_Create_Generic_View, basic)
{
  Vector<int> V1(1);
  Tiny_Vector<int, 2> V2;

  auto V1_generic_view = V1.as_generic_view();
  auto V2_generic_view = V2.as_generic_view();

  // Check that we get the _same_ expected type
  EXPECT_TRUE((std::is_same_v<decltype(V1_generic_view), decltype(V2_generic_view)>));
  EXPECT_TRUE((std::is_same_v<decltype(V1_generic_view), Generic_Vector_View<int>>));
  EXPECT_TRUE((std::is_same_v<decltype(V2_generic_view), Generic_Vector_View<int>>));

  //================================================================

  const Vector<int> const_V1(1);
  const Tiny_Vector<int, 2> const_V2;

  auto const_V1_generic_view = const_V1.as_generic_view();
  auto const_V2_generic_view = const_V2.as_generic_view();

  // check we get same  the _same_ expected _const_ type
  EXPECT_TRUE((std::is_same_v<decltype(const_V1_generic_view), decltype(const_V2_generic_view)>));
  EXPECT_FALSE((std::is_same_v<decltype(V1_generic_view), decltype(const_V1_generic_view)>));

  EXPECT_TRUE((std::is_same_v<decltype(const_V1_generic_view), Generic_Vector_Const_View<int>>));
  EXPECT_TRUE((std::is_same_v<decltype(const_V2_generic_view), Generic_Vector_Const_View<int>>));

  //================================================================

  auto const2_V1_generic_view = V1.as_generic_const_view();
  auto const2_V2_generic_view = V2.as_generic_const_view();

  EXPECT_TRUE((std::is_same_v<decltype(const2_V1_generic_view), decltype(const_V1_generic_view)>));
  EXPECT_TRUE((std::is_same_v<decltype(const2_V2_generic_view), decltype(const_V2_generic_view)>));

  //================================================================
  // Check involution: view of view is also view

  auto view_V1_generic_view = V1_generic_view.as_generic_view();

  EXPECT_TRUE((std::is_same_v<decltype(view_V1_generic_view), decltype(V1_generic_view)>));

  auto const_view_V1_generic_view = const_V1_generic_view.as_generic_view();

  EXPECT_TRUE(
      (std::is_same_v<decltype(const_view_V1_generic_view), decltype(const_V1_generic_view)>));
}

TEST(Vector_Create_Generic_View, test_alias)
{
  Tiny_Vector<int, 2> V1;

  auto view_V1 = V1.as_generic_view();
  EXPECT_TRUE((std::is_same_v<decltype(view_V1), Generic_Vector_View<int>>));

  auto const_view_V1 = V1.as_generic_const_view();
  EXPECT_TRUE((std::is_same_v<decltype(const_view_V1), Generic_Vector_Const_View<int>>));
}
