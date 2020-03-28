#include "LinearAlgebra/expr/M_assign_alpha_M.hpp"
#include "LinearAlgebra/expr/V_assign_alpha_V.hpp"

#include "LinearAlgebra/metaexpr/call_assign_from_metaexpr.hpp"

#include "LinearAlgebra/metaexpr/operator_overloading.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Call_Assign_From_Metaexpr, V0_assign_alpha_V0)
{
  Tiny_Vector<int, 2> vector;

  vector[0] = 10;

  auto expression = 4 * vector;

  EXPECT_EQ(vector[0], 10);

  auto selected = Detail::call_assign_from_metaexpr(vector, expression);
  EXPECT_EQ(selected, Expr_Selector_Enum::Generic);

  EXPECT_EQ(vector[0], 40);

  // vector class
  //
  EXPECT_EQ(vector[0], 40);

  vector = 2 * vector;

  EXPECT_EQ(vector[0], 80);
}

TEST(Call_Assign_From_Metaexpr, M0_assign_alpha_M0)
{
  Tiny_Matrix<int, 2, 3> matrix;

  matrix(0, 0) = 10;

  auto expression = 4 * matrix;

  EXPECT_EQ(matrix(0, 0), 10);

  auto selected = Detail::call_assign_from_metaexpr(matrix, expression);
  EXPECT_EQ(selected, Expr_Selector_Enum::Static);

  // matrix class
  //
  EXPECT_EQ(matrix(0, 0), 40);

  matrix = 2 * matrix;

  EXPECT_EQ(matrix(0, 0), 80);
}
