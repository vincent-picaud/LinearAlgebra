#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Dimension, vector_dimension)
{
  Tiny_Vector<int, 3> V;
  Vector<int> W(2);

  auto V_dim = dimension_predicate(V);
  auto W_dim = dimension_predicate(W);

  EXPECT_TRUE(V_dim);
  EXPECT_TRUE(W_dim);

  EXPECT_EQ(V_dim.size(), 3);
  EXPECT_EQ(W_dim.size(), 2);

  EXPECT_FALSE(V_dim + W_dim);
  EXPECT_TRUE(V_dim + V_dim);
  EXPECT_TRUE(W_dim + W_dim);

  EXPECT_EQ((V_dim + V_dim).size(), 3);
  EXPECT_EQ((W_dim + W_dim).size(), 2);
}

TEST(Dimension, matrix_dimension)
{
  Tiny_Matrix<int, 3, 2> M;
  auto M_dim = dimension_predicate(M);

  EXPECT_EQ(M_dim.I_size(), 3);
  EXPECT_EQ(M_dim.J_size(), 2);

  EXPECT_FALSE(M_dim * M_dim);

  auto Mt_dim = matrix_op(_transConj_, M_dim);

  EXPECT_EQ(Mt_dim.I_size(), 2);
  EXPECT_EQ(Mt_dim.J_size(), 3);

  auto M_Mt_dim = M_dim * Mt_dim;

  EXPECT_TRUE(M_Mt_dim);

  EXPECT_EQ(M_Mt_dim.I_size(), 3);
  EXPECT_EQ(M_Mt_dim.J_size(), 3);

  /////////////////

  auto M_p_Mt_dim = M_dim + Mt_dim;

  EXPECT_FALSE(M_p_Mt_dim);

  auto M_p_M_dim = M_dim + M_dim;

  EXPECT_TRUE(M_p_M_dim);
  EXPECT_EQ(M_p_M_dim.I_size(), 3);
  EXPECT_EQ(M_p_M_dim.J_size(), 2);
}
