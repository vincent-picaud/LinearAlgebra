#include "LinearAlgebra/expr_of_the_poor/known_patterns_impl.hpp"
#include "LinearAlgebra/expr_of_the_poor/V0_assign_alpha_V0_plus_beta_op_M_V1.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Known_Pattern, axpy)
{
  Tiny_Vector<int, 3> v;
  Vector<int> w(3);

  iota(v, 1);
  iota(w, 5);

  expr(v, _assign_, _vector_0_, _plus_, 2, w);

  EXPECT_EQ(v[0], 1 + 2 * w[0]);
  EXPECT_EQ(v[1], 2 + 2 * w[1]);
  EXPECT_EQ(v[2], 3 + 2 * w[2]);
}

TEST(Known_Pattern, Rank_One_Update)
{
  Tiny_Vector<int, 3> v;
  Symmetric_Matrix<float> S(3, 3);

  iota(v, 1);

  expr(S, _assign_, 0, _matrix_0_, _plus_, 2, v, _transpose_, _vector_1_);

  std::cerr << "\nS\n" << S;

  EXPECT_EQ(S(0, 0), 2);
  EXPECT_EQ(S(1, 0), 4);
  EXPECT_EQ(S(2, 0), 6);

  EXPECT_EQ(S(1, 1), 8);
  EXPECT_EQ(S(2, 1), 12);

  EXPECT_EQ(S(2, 2), 18);
}

TEST(Known_Pattern, Mat_Vect_Prod)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<int, 2> w;
  Tiny_Matrix<int, 2, 3> M;

  iota(v, 1);

  expr(v, _assign_, 10);
  expr(M, _assign_, 1);

  expr(w, _assign_, 0, _vector_0_, _plus_, 2, _identity_, M, v);

  EXPECT_TRUE(true);
}

TEST(Known_Pattern, Sym_Mat_Vect_Prod)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<int, 3> w;
  Tiny_Symmetric_Matrix<int, 3> M;

  iota(v, 1);

  int count = 0;
  M.map([&count](auto& m_ij) {
    m_ij = count;
    ++count;
  });

  expr(w, _assign_, 0, _vector_0_, _plus_, 2, _identity_, M, v);

  EXPECT_EQ(w[0], 16);
  EXPECT_EQ(w[1], 38);
  EXPECT_EQ(w[2], 50);

  expr(w, _assign_, 4, _vector_0_, _plus_, 2, _identity_, M, v);

  EXPECT_EQ(w[0], 80);
  EXPECT_EQ(w[1], 190);
  EXPECT_EQ(w[2], 250);
}

TEST(Known_Pattern, Herm_Mat_Vect_Prod)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<std::complex<int>, 3> w;
  Tiny_Hermitian_Matrix<std::complex<int>, 3> M;

  iota(v, 1);

  int count = 0;
  M.map_indexed([&count](auto& m_ij, const size_t i, const size_t j) {
    if (i != j)
    {
      m_ij = std::complex<int>(count, 4 * count);
    }
    else
    {
      m_ij = count;
    }
    ++count;
  });

  expr(w, _assign_, std::complex<int>(0), _vector_0_, _plus_, std::complex<int>(2), _identity_, M, v);

  EXPECT_EQ(w[0], std::complex<int>(16, -64));
  EXPECT_EQ(w[1], std::complex<int>(38, -88));
  EXPECT_EQ(w[2], std::complex<int>(50, 80));

  expr(w, _assign_, 4, _vector_0_, _plus_, 2, _identity_, M, v);

  EXPECT_EQ(w[0], std::complex<int>(80, -320));
  EXPECT_EQ(w[1], std::complex<int>(190, -440));
  EXPECT_EQ(w[2], std::complex<int>(250, 400));
}

TEST(Known_Pattern, Lower_Triangular_Strict_Vect_Prod)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<int, 3> w;
  Tiny_Lower_Triangular_Strict_Matrix<int, 3, 3> M;

  iota(v, 1);

  int count = 1;
  M.map([&count](auto& m_ij) {
    m_ij = count;
    ++count;
  });

  expr(w, _assign_, 0, _vector_0_, _plus_, 2, _transpose_, M, v);

  EXPECT_EQ(w[0], 16);
  EXPECT_EQ(w[1], 18);
  EXPECT_EQ(w[2], 0);

  expr(w, _assign_, 4, _vector_0_, _plus_, 2, _identity_, M, v);

  EXPECT_EQ(w[0], 64);
  EXPECT_EQ(w[1], 74);
  EXPECT_EQ(w[2], 16);
}

TEST(Known_Pattern, Unit_Triangular_Upper_Vect_Prod)
{
  Tiny_Vector<int, 3> v;
  Tiny_Vector<int, 3> w;
  Tiny_Upper_Unit_Triangular_Matrix<int, 3, 3> M;

  iota(v, 1);

  int count = 1;
  M.map([&count](auto& m_ij) {
    m_ij = count;
    ++count;
  });

  expr(w, _assign_, 0, _vector_0_, _plus_, 2, _transpose_, M, v);

  EXPECT_EQ(w[0], 2);
  EXPECT_EQ(w[1], 6);
  EXPECT_EQ(w[2], 22);

  expr(w, _assign_, 4, _vector_0_, _plus_, 2, _identity_, M, v);

  EXPECT_EQ(w[0], 26);
  EXPECT_EQ(w[1], 46);
  EXPECT_EQ(w[2], 94);
}
