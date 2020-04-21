#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_VX_header.hpp"

#include "LinearAlgebra/metaexpr/metaexpr.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_alpha_op_M_V1_plus_beta_VX_header, alias)
{
  Vector<double> V(4), W(4);
  Matrix<double> M(4, 4);

  V = 1 * transpose(M) * W + 1 * V;

  V = +transpose(M) * W + 1 * V;
  V = -transpose(M) * W + 1 * V;

  V = 1 * transpose(M) * W + V;
  V = 1 * transpose(M) * W - V;

  V = transpose(M) * W + V;
  V = transpose(M) * W - V;

  V = -transpose(M) * W + V;
  V = -transpose(M) * W - V;

  V = 1 * M * W + 1 * V;

  // V = +M * W + 1 * V;
  V = -M * W + 1 * V;

  V = 1 * M * W + V;
  V = 1 * M * W - V;

  V = M * W + V;
  V = M * W - V;

  V = -M * W + V;
  V = -M * W - V;

  // reverse order
  V = 1 * V + 1 * transpose(M) * W;

  V = 1 * V + transpose(M) * W;
  V = 1 * V - transpose(M) * W;

  V = V + 1 * transpose(M) * W;
  V = -V + 1 * transpose(M) * W;

  V = V + transpose(M) * W;
  V = -V + transpose(M) * W;

  V = V - transpose(M) * W;
  V = -V - transpose(M) * W;

  // without op
  V = 1 * V + 1 * M * W;

  V = 1 * V + M * W;
  V = 1 * V - M * W;

  V = V + 1 * M * W;
  V = -V + 1 * M * W;

  V = V + M * W;
  V = -V + M * W;

  V = V - M * W;
  V = -V - M * W;
}
