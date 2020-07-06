#include "LinearAlgebra/expr/X_eq_aX_matrix.hpp"
#include "LinearAlgebra/expr/X_eq_aX_vector.hpp"

#include "LinearAlgebra/metaexpr/call_assign_from_metaexpr.hpp"

#include "LinearAlgebra/metaexpr/operator_overloading.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Call_Assign_From_Metaexpr, V0_assign_alpha_V0_bis)
{
  Tiny_Vector<std::complex<int>, 2> y;
  Tiny_Vector<int, 2> x;
  x = 5;
  DEBUG_RESET_SELECTED();
  y = std::complex<int>(3) * x;
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(y[1], std::complex<int>(3) * x[1]);
}

TEST(Call_Assign_From_Metaexpr, V0_assign_alpha_V0)
{
  Tiny_Vector<int, 2> vector;

  vector[0] = 10;

  // UB !!!
  //  auto expression = 4 * vector;

  EXPECT_EQ(vector[0], 10);

  DEBUG_RESET_SELECTED();
  Detail::call_assign_from_MetaExpr(vector, 4 * vector);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  EXPECT_EQ(vector[0], 40);

  // vector class
  //
  EXPECT_EQ(vector[0], 40);
  //  Detail::call_assign_from_MetaExpr(vector, 2 * vector);

  //  vector = Scalar_CRef(2) * vector;
  vector = 2 * vector;

  EXPECT_EQ(vector[0], 80);
}

TEST(Call_Assign_From_Metaexpr, M0_assign_alpha_M0)
{
  Tiny_Matrix<int, 2, 3> matrix;

  matrix(0, 0) = 10;

  // UB
  // auto expression = 4 * matrix;

  EXPECT_EQ(matrix(0, 0), 10);

  DEBUG_RESET_SELECTED();
  Detail::call_assign_from_MetaExpr(matrix, 4 * matrix);
  DEBUG_EXPECT_EQ(DEBUG_GET_SELECTED(), Expr_Selector_Enum::Static);

  // matrix class
  //
  EXPECT_EQ(matrix(0, 0), 40);

  matrix = 2 * matrix;

  EXPECT_EQ(matrix(0, 0), 80);
}
