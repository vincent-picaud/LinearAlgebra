// Provide the BLAS vector specialization 
//
#pragma once

#include "LinearAlgebra/expr/X0_assign_X1.hpp"

#include "LinearAlgebra/blas/blas.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //
  //================================================================
  //  Implementation: CBlas
  //================================================================
  //
  //
  // Copy operations vector_0 = vector_1
  //
  //
  // CAVEAT: out argument order convention is not the BLAS one, for instance:
  //
  //      assign(v0,v1)
  //
  //  but BLAS copy() is:
  //
  //      copy(n,v1.data(),v1.inc(),v0.data(),v0.inc())
  //
  //
#if (HAS_BLAS)
  template <typename VECTOR_0_TYPE, typename VECTOR_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<VECTOR_0_TYPE>& vector_0,       // vector_0
         const Dense_Vector_Crtp<VECTOR_1_TYPE>& vector_1  // vector_1
         )
      -> std::enable_if_t<
          Always_True_v<decltype(Blas::copy(vector_0.size(), vector_1.data(), vector_1.increment(),
                                            vector_0.data(), vector_0.increment()))>,
          Expr_Selector_Enum>
  {
    assert(are_compatible_p(vector_0, vector_1));

    Blas::copy(vector_0.size(), vector_1.data(), vector_1.increment(), vector_0.data(),
               vector_0.increment());

    return selected;
  }
#endif
}
