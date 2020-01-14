// Copy operations
#pragma once

#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"

namespace LinearAlgebra
{
  ///////////
  // V0=V1 //
  ///////////
  //

  //
  //  Generic implementation
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
