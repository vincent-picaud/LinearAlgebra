//
// Copy operations
//

//
// CAVEAT: out argument order convention is not the BLAS one, for instance:
//
//  expr(v0,_assign_,v1)
//
//  but BLAS copy() is:
//
//  copy(n,v1.data(),v1.inc(),v0.data(),v0.inc())
//
//
#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"
#include "LinearAlgebra/meta/always.hpp"
#include "LinearAlgebra/wraps/blas/blas.hpp"

namespace LinearAlgebra
{
  ///////////
  // V0=V1 //
  ///////////
  //

  //
  //  Implementation: Generic
  //
  template <typename V_0_TYPE, typename V_1_TYPE>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Generic>&,
       Default_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Default_Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
    assert(v_0.size() == v_1.size());
    v_0.map_indexed([&](auto& v_0_i, const std::size_t i) { v_0_i = v_1[i]; });
  }

  //
  //  Implementation: CBlas
  //
#if (HAS_BLAS)
  template <typename V_0_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Blas>&,
       Default_Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                               // =
       const Default_Vector_Crtp<V_1_TYPE>& v_1  // v_1
       )
      -> std::enable_if_t<Always_True_v<decltype(Blas::copy(v_0.size(), v_1.data(), v_1.increment(),
                                                            v_0.data(), v_0.increment()))>>
  {
    assert(v_0.size() == v_1.size());

    Blas::copy(v_0.size(), v_1.data(), v_1.increment(), v_0.data(), v_0.increment());
  }
#endif
  // TODO: Implementation: Static size
  //
  
  //
  // User interface
  //

  template <typename V_0_TYPE,
            typename V_1_TYPE>
  void
  expr(Vector_Crtp<V_0_TYPE>& v_0,       // v_0
       _assign_t_,                       // =
       const Vector_Crtp<V_1_TYPE>& v_1  // v_1
  )
  {
    expr(Expr_Selector<>(), v_0.impl(), _assign_, v_1.impl());
  }
}
