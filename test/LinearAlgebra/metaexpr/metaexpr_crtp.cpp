#include "LinearAlgebra/metaexpr/metaexpr_crtp.hpp"

#include "LinearAlgebra/dense/matrix.hpp"
#include "LinearAlgebra/dense/vector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(MetaExpr_Crtp, is_trivial)
{
  EXPECT_TRUE((std::is_trivially_copyable_v<
               Detail::MetaExpr_BinaryOp<double, _product_t_, Matrix<double>, Vector<double>>>));
}
