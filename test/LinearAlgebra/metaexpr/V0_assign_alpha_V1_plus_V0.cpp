//#include "LinearAlgebra/expr/X0_assign_alpha_X1_plus_X2.hpp"
#include "LinearAlgebra/expr/V0_assign_alpha_V1_plus_V2.hpp"

#include "LinearAlgebra/metaexpr/metaexpr.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/dense/vector_comparison_operators.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(V0_assign_alpha_V1_plus_V0, alias)
{
  Vector<double> V(4), W(4);

  V = V + W;
  V = V - W;

  V = V - 2 * W;
  // CAVEAT: X0 = α X2 - X1 impossible
  //  V = 2 * V - W;
}
