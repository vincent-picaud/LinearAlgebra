#include "LinearAlgebra/dense/matrix.hpp"

#include <gtest/gtest.h>
#include "LinearAlgebra/dense/matrix_view.hpp"

using namespace LinearAlgebra;

TEST(Matrix, is_trivially_copyable)
{
  using tiny_matrix_type = Tiny_Matrix<int, 3, 2>;

  // Unfortunately, being FALSE, is a side effect of our custom move
  // constructor definition
  EXPECT_FALSE((std::is_trivially_copyable_v<tiny_matrix_type>));

  using matrix_type = Matrix<int>;

  EXPECT_FALSE((std::is_trivially_copyable_v<matrix_type>));
}

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
  Default_Matrix<int,
                 Matrix_Special_Structure_Enum::None,
                 Matrix_Storage_Mask_Enum::None,
                 size_t,
                 std::integral_constant<size_t, 2>,
                 std::integral_constant<size_t, 5>>
      m(3, std::integral_constant<size_t, 2>(), std::integral_constant<size_t, 5>());

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  m(2, 1) = 10;
  EXPECT_EQ(m(2, 1), 10);
}
TEST(Matrix, weird_type_extended_constructor)
{
  Default_Matrix<int,
                 Matrix_Special_Structure_Enum::None,
                 Matrix_Storage_Mask_Enum::None,
                 size_t,
                 std::integral_constant<size_t, 2>,
                 std::integral_constant<size_t, 5>>
      m(3, 2, 5);

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  m(2, 1) = 10;
  EXPECT_EQ(m(2, 1), 10);
}

TEST(Matrix, Static_View)
{
  int d[10];

  auto m = create_matrix_view(
      d, std::integral_constant<std::size_t, 3>(), std::integral_constant<std::size_t, 2>());

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

TEST(Matrix, move)
{
  // CAVEAT: to check move operation one must use a dynamic matrix
  Matrix<double> m(3, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(2, 0) = 3;
  m(0, 1) = 4;
  m(1, 1) = 5;
  m(2, 1) = 6;

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(1, 0), 2);
  EXPECT_EQ(m(2, 0), 3);
  EXPECT_EQ(m(0, 1), 4);
  EXPECT_EQ(m(1, 1), 5);
  EXPECT_EQ(m(2, 1), 6);

  // Note: a real "move" operation is tricky to implement because one
  //       must block dynamic memory_chunk move when storage_scheme
  //       use *static* size Reason: the original matrix will be in a
  //       BROKEN state after the move (data()=nullptr, but size!=0)
  //
  auto m2(std::move(m));

  EXPECT_EQ(m2.I_size(), 3);
  EXPECT_EQ(m2.J_size(), 2);

  EXPECT_EQ(m.I_size(), 0);
  EXPECT_EQ(m.J_size(), 0);
  EXPECT_TRUE(m.data() != m2.data());  // check that m is really moved
  EXPECT_TRUE(m.data() == nullptr);

  EXPECT_EQ(m2(0, 0), 1);
  EXPECT_EQ(m2(1, 0), 2);
  EXPECT_EQ(m2(2, 0), 3);
  EXPECT_EQ(m2(0, 1), 4);
  EXPECT_EQ(m2(1, 1), 5);
  EXPECT_EQ(m2(2, 1), 6);

  // EXPECT_EQ(m.I_size(), 0);
  // EXPECT_EQ(m.J_size(), 0);
  // EXPECT_EQ(m.data(), nullptr);
}

TEST(Matrix, move_dynamic_but_static_sizes)
{
  // CAVEAT: to check move operation one must use a dynamic matrix,
  //         but here we have static size that must prevent from
  //         "moving" the memory chunk
  Default_Matrix<int,
                 Matrix_Special_Structure_Enum::None,
                 Matrix_Storage_Mask_Enum::None,
                 std::integral_constant<size_t, 3>,
                 std::integral_constant<size_t, 2>,
                 std::integral_constant<size_t, 5>>
      m;

  m(0, 0) = 1;
  m(1, 0) = 2;
  m(2, 0) = 3;
  m(0, 1) = 4;
  m(1, 1) = 5;
  m(2, 1) = 6;

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);

  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(1, 0), 2);
  EXPECT_EQ(m(2, 0), 3);
  EXPECT_EQ(m(0, 1), 4);
  EXPECT_EQ(m(1, 1), 5);
  EXPECT_EQ(m(2, 1), 6);

  // Note: a real "move" operation is tricky to implement because one
  //       must block dynamic memory_chunk move when storage_scheme
  //       use *static* size Reason: the original matrix will be in a
  //       BROKEN state after the move (data()=nullptr, but size!=0)
  //
  auto p_m = m.data();
  auto m2(std::move(m));

  EXPECT_EQ(m2.I_size(), 3);
  EXPECT_EQ(m2.J_size(), 2);

  EXPECT_EQ(m.I_size(), 3);
  EXPECT_EQ(m.J_size(), 2);
  EXPECT_TRUE(m.data() != m2.data());  // check that static sizes have
                                       // blocked to memory_chunk move
  EXPECT_TRUE(m.data() == p_m);

  EXPECT_EQ(m2(0, 0), 1);
  EXPECT_EQ(m2(1, 0), 2);
  EXPECT_EQ(m2(2, 0), 3);
  EXPECT_EQ(m2(0, 1), 4);
  EXPECT_EQ(m2(1, 1), 5);
  EXPECT_EQ(m2(2, 1), 6);
}

TEST(Matrix, view_empty_constructor)
{
  Generic_Matrix_Const_View<int,
                            Matrix_Special_Structure_Enum::None,
                            Matrix_Storage_Mask_Enum::None>
      V1;
  Generic_Matrix_View<int, Matrix_Special_Structure_Enum::None, Matrix_Storage_Mask_Enum::None> V2;
  Default_Matrix_View<int,
                      Matrix_Special_Structure_Enum::None,
                      Matrix_Storage_Mask_Enum::None,
                      std::integral_constant<size_t, 3>,
                      std::integral_constant<size_t, 2>,
                      std::integral_constant<size_t, 5>>
      V3;

  EXPECT_TRUE(V1.data() == nullptr);
  EXPECT_TRUE(V2.data() == nullptr);
  EXPECT_TRUE(V3.data() == nullptr);
}

TEST(Matrix, view_empty_constructor_debug_death)
{
  Default_Matrix_View<int,
                      Matrix_Special_Structure_Enum::None,
                      Matrix_Storage_Mask_Enum::None,
                      std::integral_constant<size_t, 3>,
                      std::integral_constant<size_t, 2>,
                      std::integral_constant<size_t, 5>>
      V;

  EXPECT_DEBUG_DEATH(V(0, 0), "");
}

// XXXx

//----------------------------------------------------------------
TEST(Matrix, construction_mixed_type_1)
{
  Matrix<int> v(3, 3);
  v = 1;
  Tiny_Matrix<double, 3, 3> w(v);
  EXPECT_EQ(w(0,0), 1);
  EXPECT_EQ(w(1,0), 1);
  EXPECT_EQ(w(2,0), 1);

  // Check that we really perform a copy
  v(1,0) = 2;
  EXPECT_EQ(w(1,0), 1);
}
TEST(Matrix, construction_mixed_type_2)
{
  Tiny_Matrix<double, 3, 3> v;
  v = 1;
  Matrix<int> w(v);
  EXPECT_EQ(w(0,0), 1);
  EXPECT_EQ(w(1,0), 1);
  EXPECT_EQ(w(2,0), 1);

  // Check that we really perform a copy
  v(1,0) = 2;
  EXPECT_EQ(w(1,0), 1);
}
TEST(Matrix, construction_mixed_type_3)
{
  Matrix<double> v(3, 3);
  v = 1;
  Matrix<int> w(v.as_generic_view());
  EXPECT_EQ(w(0,0), 1);
  EXPECT_EQ(w(1,0), 1);
  EXPECT_EQ(w(2,0), 1);

  // Check that we really perform a copy
  v(1,0) = 2;
  EXPECT_EQ(w(1,0), 1);
}
//----------------------------------------------------------------
TEST(Matrix, extended_constructor_for_static_size)
{
  Tiny_Matrix<int, 3, 3> v(3, 3);
  EXPECT_EQ(v.I_size(), 3);
}
TEST(Matrix, extended_constructor_for_static_size_check)
{
  EXPECT_DEBUG_DEATH((Tiny_Matrix<int, 3, 3>(3, 4)), "");
}
