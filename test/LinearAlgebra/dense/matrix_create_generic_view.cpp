#include "LinearAlgebra/dense/matrix_create_generic_view.hpp"

#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Matrix_Create_Generic_View, basic)
{
  Matrix<int> M1(1, 2);
  Tiny_Matrix<int, 2, 4> M2;

  auto M1_generic_view = create_generic_view(M1);
  auto M2_generic_view = create_generic_view(M2);

  // Check that we get the _same_ expected type
  EXPECT_TRUE((std::is_same_v<decltype(M1_generic_view), decltype(M2_generic_view)>));
  EXPECT_TRUE((std::is_same_v<decltype(M1_generic_view), Generic_Matrix_View<int>>));
  EXPECT_TRUE((std::is_same_v<decltype(M2_generic_view), Generic_Matrix_View<int>>));

  //================================================================

  const Matrix<int> const_M1(1, 2);
  const Tiny_Matrix<int, 2, 4> const_M2;

  auto const_M1_generic_view = create_generic_view(const_M1);
  auto const_M2_generic_view = create_generic_view(const_M2);

  // check we get same  the _same_ expected _const_ type
  EXPECT_TRUE((std::is_same_v<decltype(const_M1_generic_view), decltype(const_M2_generic_view)>));
  EXPECT_FALSE((std::is_same_v<decltype(M1_generic_view), decltype(const_M1_generic_view)>));

  EXPECT_TRUE((std::is_same_v<decltype(const_M1_generic_view), Generic_Matrix_Const_View<int>>));
  EXPECT_TRUE((std::is_same_v<decltype(const_M2_generic_view), Generic_Matrix_Const_View<int>>));

  //================================================================

  auto const2_M1_generic_view = create_generic_view(M1.as_const());
  auto const2_M2_generic_view = create_generic_view(M2.as_const());

  EXPECT_TRUE((std::is_same_v<decltype(const2_M1_generic_view), decltype(const_M1_generic_view)>));
  EXPECT_TRUE((std::is_same_v<decltype(const2_M2_generic_view), decltype(const_M2_generic_view)>));

  //================================================================
  // Check involution: view of view is also view

  auto view_M1_generic_view = create_generic_view(M1_generic_view);

  EXPECT_TRUE((std::is_same_v<decltype(view_M1_generic_view), decltype(M1_generic_view)>));

  auto const_view_M1_generic_view = create_generic_view(const_M1_generic_view);

  EXPECT_TRUE(
      (std::is_same_v<decltype(const_view_M1_generic_view), decltype(const_M1_generic_view)>));
}

TEST(Matrix_Create_Generic_View, test_alias)
{
  Tiny_Matrix<int, 2, 4> M1;

  auto view_M1 = create_generic_view(M1);
  EXPECT_TRUE((std::is_same_v<decltype(view_M1), Generic_Matrix_View<int>>));

  auto const_view_M1 = create_generic_view(M1.as_const());
  EXPECT_TRUE((std::is_same_v<decltype(const_view_M1), Generic_Matrix_Const_View<int>>));
}

TEST(Matrix_Create_Generic_View, test_alias_symmetric)
{
  Tiny_Symmetric_Matrix<int, 2> M1;

  auto view_M1 = create_generic_view(M1);
  EXPECT_TRUE((std::is_same_v<decltype(view_M1), Generic_Symmetric_Matrix_View<int>>));

  auto const_view_M1 = create_generic_view(M1.as_const());
  EXPECT_TRUE((std::is_same_v<decltype(const_view_M1), Generic_Symmetric_Matrix_Const_View<int>>));
}
