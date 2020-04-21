#include "LinearAlgebra/expr/expr_debug.hpp"

namespace LinearAlgebra
{
#ifndef NDEBUG
  namespace Detail
  {
    Expr_Selector_Enum debug_selected = Expr_Selector_Enum::Undefined;
  }
#endif
}
