//
// The used trick to check selected method in unit tests
//
#pragma once

#include "LinearAlgebra/expr/expr_selector.hpp"

namespace LinearAlgebra::Detail
{
#ifndef NDEBUG

  extern Expr_Selector_Enum debug_selected;

#define DEBUG_RESET_SELECTED() LinearAlgebra::Detail::debug_selected = Expr_Selector_Enum::END
#define DEBUG_GET_SELECTED() (LinearAlgebra::Detail::debug_selected)
#define DEBUG_SET_SELECTED(value) LinearAlgebra::Detail::debug_selected = (value)

#else

#define DEBUG_RESET_SELECTED()
#define DEBUG_GET_SELECTED()
#define DEBUG_SET_SELECTED(value) (void)value

#endif

  // TODO (not urgent): maybe move into test/ directory
#ifndef NDEBUG
#define DEBUG_EXPECT_EQ(A, B) EXPECT_EQ((A), (B))
#else
#define DEBUG_EXPECT_EQ(A, B)
#endif

}
