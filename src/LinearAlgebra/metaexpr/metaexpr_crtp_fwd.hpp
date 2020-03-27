// Forward declaration that are used by vector, matrix etc...

#pragma once

namespace LinearAlgebra
{
  namespace Detail
  {
    template <typename IMPL>
    class MetaExpr_Crtp;

    template <typename IMPL>
    class MetaExpr_UnaryOp_Crtp;

    template <typename IMPL>
    class MetaExpr_BinaryOp_Crtp;
  }

}
