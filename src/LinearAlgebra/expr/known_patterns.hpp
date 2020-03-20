#pragma once

#include "LinearAlgebra/dense/matrix_crtp.hpp"
#include "LinearAlgebra/dense/vector_crtp.hpp"
#include "LinearAlgebra/expr/dimension.hpp"
#include "LinearAlgebra/expr/expr_selector.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"

namespace LinearAlgebra
{
  // //****************************************************************
  // // M_0 = α.M_0 + β.v_1 transpose v_1 (rank-one udpate, M_0 is symmetric)
  // //****************************************************************
  // //
  // template <typename M_0_TYPE, typename V_1_TYPE>
  // void
  // expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
  //      Matrix_Crtp<M_0_TYPE>& M_0,                           // matrix_0
  //      _assign_t_,                                           // =
  //      const typename M_0_TYPE::element_type alpha,          // alpha
  //      _matrix_0_t_,                                         // matrix_0
  //      _plus_t_,                                             // +
  //      const typename V_1_TYPE::element_type beta,           // beta
  //      Vector_Crtp<V_1_TYPE>& v_1,                           // vector_1
  //      _transpose_t_,                                        // transpose
  //      _vector_1_t_                                          // vector_1
  // )
  // {
  //   static_assert(not(std::is_same_v<M_0_TYPE, M_0_TYPE>), "Undefined implementation");
  // }

  // template <typename M_0_TYPE, typename V_1_TYPE>
  // void
  // expr(Matrix_Crtp<M_0_TYPE>& M_0,                   // matrix_0
  //      _assign_t_,                                   // =
  //      const typename M_0_TYPE::element_type alpha,  // alpha
  //      _matrix_0_t_,                                 // matrix_0
  //      _plus_t_,                                     // +
  //      const typename V_1_TYPE::element_type beta,   // beta
  //      Vector_Crtp<V_1_TYPE>& v_1,                   // vector_1
  //      _transpose_t_,                                // transpose
  //      _vector_1_t_                                  // vector_1
  // )
  // {
  //   assert(M_0.I_size() == M_0.J_size());
  //   assert(M_0.I_size() == v_1.size());

  //   expr(Expr_Selector<>(), M_0.impl(), _assign_, alpha, _matrix_0_, _plus_, beta, v_1.impl(),
  //        _transpose_, _vector_1_);
  // }

  //****************************************************************
  // v_0 = v_0 + alpha v_1 (Blas's axpy)
  //****************************************************************
  //

  template <typename V_0, typename V_1>
  void
  expr(const Expr_Selector<Expr_Selector_Enum::Undefined>&,  // Undefined implementation
       Vector_Crtp<V_0>& v_0,                                // vector_0
       _assign_t_,                                           // =
       _vector_0_t_,                                         // vector_0
       _plus_t_,                                             // +
       const typename V_1::element_type scalar,              // scalar
       const Vector_Crtp<V_1>& v_1                           // vector_1
  )
  {
    static_assert(not(std::is_same_v<V_0, V_0>), "Undefined implementation");
  }

  template <typename V_0, typename V_1>
  void
  expr(Vector_Crtp<V_0>& v_0,                    // vector_0
       _assign_t_,                               // =
       _vector_0_t_,                             // vector_0
       _plus_t_,                                 // +
       const typename V_1::element_type scalar,  // scalar
       const Vector_Crtp<V_1>& v_1               // vector_1
  )
  {
    assert(v_0.size() == v_1.size());

    expr(Expr_Selector<>(), v_0.impl(), _assign_, _vector_0_, _plus_, scalar, v_1.impl());
  }

}
