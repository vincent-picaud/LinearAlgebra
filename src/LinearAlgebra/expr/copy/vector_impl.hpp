#pragma once

#include "LinearAlgebra/expr/copy/generic_interface.hpp"

#include "LinearAlgebra/blas/blas.hpp"
#include "LinearAlgebra/dense/vector_fill.hpp"

namespace LinearAlgebra
{
  //////////////////////////////////////////////////////////////////
  // Implementation
  //////////////////////////////////////////////////////////////////
  //

  //================================================================
  //  Implementation: Generic
  //================================================================
  //
  template <typename X0_TYPE, typename X1_TYPE>
  void
  assign(const Expr_Selector<Expr_Selector_Enum::Generic> selected,
         Dense_Vector_Crtp<X0_TYPE>& X0,
         const Dense_Vector_Crtp<X1_TYPE>& X1)
  {
    assign_helper(X0, X1);

    DEBUG_SET_SELECTED(selected);
  }

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
         ) -> std::enable_if_t<Always_True_v<decltype(Blas::copy(vector_0.size(),
                                                                 vector_1.data(),
                                                                 vector_1.increment(),
                                                                 vector_0.data(),
                                                                 vector_0.increment()))>>
  {
    assert(are_compatible_p(vector_0, vector_1));

    Blas::copy(vector_0.size(),
               vector_1.data(),
               vector_1.increment(),
               vector_0.data(),
               vector_0.increment());

    DEBUG_SET_SELECTED(selected);
  }
#endif

  //================================================================
  //  Implementation: Static
  //================================================================
  //
  // Role: skip Blas when dimension are static
  //
  template <typename X0_TYPE, typename X1_TYPE>
  std::enable_if_t<Any_Has_Static_Dimension_v<X0_TYPE, X1_TYPE>>
  assign(const Expr_Selector<Expr_Selector_Enum::Static> selected,
         Dense_Vector_Crtp<X0_TYPE>& X0,
         const Dense_Vector_Crtp<X1_TYPE>& X1)
  {
    assign_helper(X0, X1);

    DEBUG_SET_SELECTED(selected);
  }
}
