#include "LinearAlgebra/expr/X0_assign_X1.hpp"

//#include "LinearAlgebra/expr/V0_assign_V1.hpp"

#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_view.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V_assign_V, copy)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  Vector<int> w(3);
  w[0] = 0;
  w[1] = 0;
  w[2] = 0;

  Expr_Selector_Enum selected = assign(w, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);
}

TEST(V_assign_V, copy_blas)
{
  Vector<float> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  Vector<float> w(3);
  w[0] = 0;
  w[1] = 0;
  w[2] = 0;

  Expr_Selector_Enum selected = assign(w, v);

  EXPECT_EQ(selected, Expr_Selector_Enum::Blas);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);
}

TEST(V_assign_V, copy_assert)
{
  Tiny_Vector<int, 3> v;
  auto selected = assign(v, v);
  EXPECT_EQ(selected, Expr_Selector_Enum::END);  // "nothing to do" detected
}

TEST(V_assign_V, copy_assert_2)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<int, 2> w;
  EXPECT_DEBUG_DEATH(assign(v, w), "");
}

TEST(V_assign_V, overloaded_operator)
{
  Tiny_Vector<int, 3> v;
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  Vector<int> w(3);
  w[0] = 0;
  w[1] = 0;
  w[2] = 0;

  w = v;

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);

  EXPECT_EQ(w[0], 1);
  EXPECT_EQ(w[1], 2);
  EXPECT_EQ(w[2], 3);
}

// Note: fundamental to understand to properly use this library!
//
TEST(V_assign_V, copy_semantic)
{
  int data[5] = {1, 2, 3, 4, 5};
  int data_2[5];

  // Construction from the raw type
  Default_Vector_View<int, size_t, size_t> view(data, 5, 1);

  Vector<int> v_cpy(5);

  v_cpy = view;
  EXPECT_EQ(v_cpy[0], 1);
  EXPECT_EQ(v_cpy[1], 2);
  EXPECT_EQ(v_cpy[2], 3);
  EXPECT_EQ(v_cpy[3], 4);
  EXPECT_EQ(v_cpy[4], 5);

  Default_Vector_View<int, size_t, size_t> view_2(data_2, 5, 1);

  EXPECT_EQ(view_2.data(), data_2);
  view_2 = view;                     // Here a deep copy! (SAME semantic as storable v_cpy)
  EXPECT_EQ(view_2.data(), data_2);  // and NOT a simple pointer copy!
  EXPECT_EQ(view.data(), data);

  EXPECT_EQ(view_2[0], 1);
  EXPECT_EQ(view_2[1], 2);
  EXPECT_EQ(view_2[2], 3);
  EXPECT_EQ(view_2[3], 4);
  EXPECT_EQ(view_2[4], 5);

  //================

  v_cpy[2] = 30;

  view_2 = v_cpy;  // also a deep copy here

  EXPECT_EQ(view_2.data(), data_2);
  EXPECT_EQ(view_2[0], 1);
  EXPECT_EQ(view_2[1], 2);
  EXPECT_EQ(view_2[2], 30);
  EXPECT_EQ(view_2[3], 4);
  EXPECT_EQ(view_2[4], 5);
}
