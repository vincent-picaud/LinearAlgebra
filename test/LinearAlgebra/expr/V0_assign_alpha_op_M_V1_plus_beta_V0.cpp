#include "LinearAlgebra/matrix.hpp"
#include "LinearAlgebra/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_alpha_op_M_V1_plus_beta_V0, blas_gemv)
{
  using T = double;

  Tiny_Matrix<T, 3, 2> M;
  Vector<T> y(3);
  Tiny_Vector<T, 2> x;

  M(0, 0) = 1;
  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;
  M(2, 0) = 1;
  M(2, 1) = 1;

  x[0] = 1;
  x[1] = 2;

  DEBUG_RESET_SELECTED();
  assign(y,
         _plus_,
         _product_,
         _product_,
         Scalar<T>(2),
         _identity_,
         M,
         x,
         _product_,
         Scalar<T>(0),
         _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  EXPECT_EQ(y[0], 2 * x[0]);
  EXPECT_EQ(y[1], 2 * x[1]);
  EXPECT_EQ(y[2], 2 * (x[0] + x[1]));
}

TEST(V0_assign_alpha_op_M_V1_plus_beta_V0, blas_symv)
{
  using T = double;

  Tiny_Symmetric_Matrix<T, 3> M;
  Vector<T> y(3);
  Tiny_Vector<T, 3> x;

  M(0, 0) = 1;
  //  M(0, 1) = 0;
  M(1, 0) = 0;
  M(1, 1) = 1;

  M(2, 0) = 1;
  M(2, 1) = 1;
  M(2, 2) = 1;

  x[0] = 1;
  x[1] = 2;

  auto y_cpy_as_int = similar(Type_v<int>, y);

  DEBUG_RESET_SELECTED();
  assign(y,
         _plus_,
         _product_,
         _product_,
         Scalar<T>(2),
         _identity_,
         M,
         x,
         _product_,
         Scalar<T>(0),
         _lhs_);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Blas);

  // y_cpy_as_int = 2 * transpose(M) * x + 0 * y_cpy_as_int;
  // EXPECT_EQ(y, y_cpy_as_int);
}

//=============

// TEST(Known_Pattern, Mat_Vect_Prod)
// {
//   Tiny_Vector<int, 3> v;
//   Tiny_Vector<int, 2> w;
//   Tiny_Matrix<int, 2, 3> M;

//   iota(v, 1);

//   v = 10;
//   M = 1;

//   assign(w, 2, _identity_, M, v, _plus_, 0, _lhs_);

//   EXPECT_TRUE(true);
// }

// TEST(Known_Pattern, Sym_Mat_Vect_Prod)
// {
//   Tiny_Vector<int, 3> v;
//   Tiny_Vector<int, 3> w;
//   Tiny_Symmetric_Matrix<int, 3> M;

//   iota(v, 1);

//   int count = 0;
//   fill([&count]() { return count++; }, M);

//   assign(w, 2, _identity_, M, v, _plus_, 0, _lhs_);

//   EXPECT_EQ(w[0], 16);
//   EXPECT_EQ(w[1], 38);
//   EXPECT_EQ(w[2], 50);

//   assign(w, 2, _identity_, M, v, _plus_, 4, _lhs_);

//   EXPECT_EQ(w[0], 80);
//   EXPECT_EQ(w[1], 190);
//   EXPECT_EQ(w[2], 250);
// }

// TEST(Known_Pattern, Herm_Mat_Vect_Prod)
// {
//   Tiny_Vector<int, 3> v;
//   Tiny_Vector<std::complex<int>, 3> w;
//   Tiny_Hermitian_Matrix<std::complex<int>, 3> M;

//   iota(v, 1);

//   int count = 0;
//   fill_indexed(
//       [&count](const size_t i, const size_t j) {
//         auto m_ij = (i != j) ? std::complex<int>(count, 4 * count) : count;
//         ++count;
//         return m_ij;
//       },
//       M);

//   // does not compile ANYMORE
//   // something has changed.... TO FIX

//   //  expr(w, _assign_, std::complex<int>(0), _lhs_, _plus_, std::complex<int>(2), _identity_, M, v);

//   // EXPECT_EQ(w[0], std::complex<int>(16, -64));
//   // EXPECT_EQ(w[1], std::complex<int>(38, -88));
//   // EXPECT_EQ(w[2], std::complex<int>(50, 80));

//   //  expr(w, _assign_, 2, _identity_, M, v, _plus_, 4, _lhs_);

//   // EXPECT_EQ(w[0], std::complex<int>(80, -320));
//   // EXPECT_EQ(w[1], std::complex<int>(190, -440));
//   // EXPECT_EQ(w[2], std::complex<int>(250, 400));
// }

// TEST(Known_Pattern, Strict_Lower_Triangular_Vect_Prod)
// {
//   Tiny_Vector<int, 3> v;
//   Tiny_Vector<int, 3> w;
//   Tiny_Strict_Lower_Triangular_Matrix<int, 3, 3> M;

//   iota(v, 1);

//   int count = 1;
//   fill([&count]() { return count++; }, M);

//   assign(w, 2, _transpose_, M, v, _plus_, 0, _lhs_);

//   EXPECT_EQ(w[0], 16);
//   EXPECT_EQ(w[1], 18);
//   EXPECT_EQ(w[2], 0);

//   assign(w, 2, _identity_, M, v, _plus_, 4, _lhs_);

//   EXPECT_EQ(w[0], 64);
//   EXPECT_EQ(w[1], 74);
//   EXPECT_EQ(w[2], 16);
// }

// TEST(Known_Pattern, Unit_Triangular_Upper_Vect_Prod)
// {
//   Tiny_Vector<int, 3> v;
//   Tiny_Vector<int, 3> w;
//   Tiny_Unit_Upper_Triangular_Matrix<int, 3, 3> M;

//   iota(v, 1);

//   int count = 1;
//   fill([&count]() { return count++; }, M);

//   assign(w, 2, _transpose_, M, v, _plus_, 0, _lhs_);

//   EXPECT_EQ(w[0], 2);
//   EXPECT_EQ(w[1], 6);
//   EXPECT_EQ(w[2], 22);

//   assign(w, 2, _identity_, M, v, _plus_, 4, _lhs_);

//   EXPECT_EQ(w[0], 26);
//   EXPECT_EQ(w[1], 46);
//   EXPECT_EQ(w[2], 94);
// }
