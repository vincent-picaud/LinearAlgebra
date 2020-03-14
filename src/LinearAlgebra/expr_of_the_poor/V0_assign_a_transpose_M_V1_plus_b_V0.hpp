//
// Compute: V0 = α op(M).V1 + β.V0
//

#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/matrix_special_structure_enum.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_selector.hpp"
#include "LinearAlgebra/expr_of_the_poor/expr_tags.hpp"
#include "LinearAlgebra/meta/always.hpp"
#include "LinearAlgebra/meta/element_type.hpp"

#include "LinearAlgebra/wraps/blas/to_cblas_transpose.hpp"
#include "LinearAlgebra/wraps/blas/blas_subroutines.hpp"

namespace LinearAlgebra
{
  //
  // User interface
  //

  //
  //  Implementation: CBlas
  //
#if (HAS_BLAS)
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum OP_M, typename M_TYPE, typename V_1_TYPE>
  auto
  expr(const Expr_Selector<Expr_Selector_Enum::Blas>,
       Default_Vector_Crtp<V_0_TYPE>& v_0,        // v_0
       _assign_t_,                                // =
       const Element_Type_t<M_TYPE>& alpha,       // α
       const _matrix_unary_op_t_<OP_M>,           // op
       const Default_Matrix_Crtp<M_TYPE>& M,      // M
       const Default_Vector_Crtp<V_1_TYPE>& v_1,  // v_1
       const _plus_t_,                            // +
       const Element_Type_t<M_TYPE>& beta,        // β
       const _vector_0_t_                         // v_0

       )
      -> std::enable_if_t<
          // Blas function availability?
          Always_True_v<decltype(Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<OP_M>,
                                            M.I_size(), M.J_size(), alpha, M.data(),
                                            M.leading_dimension(), v_1.data(), v_1.increment(),
                                            beta, v_0.data(), v_0.increment()))> &&
          // Supported matrix op?
          Always_True_v<decltype(Blas::To_CBlas_Transpose_v<OP_M>)> &&
          // Generic matrix
          (M_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None)>
  {
    Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<OP_M>, M.I_size(), M.J_size(), alpha,
               M.data(), M.leading_dimension(), v_1.data(), v_1.increment(), beta, v_0.data(),
               v_0.increment());
  }
#endif

  //
  // User interface
  //
  template <typename V_0_TYPE, Matrix_Unary_Op_Enum OP_M, typename M_TYPE,
            typename V_1_TYPE>
  void
  expr(Vector_Crtp<V_0_TYPE>& v_0,           // v_0
       _assign_t_,                           // =
       const Element_Type_t<M_TYPE>& alpha,  // α
       const _matrix_unary_op_t_<OP_M>,      // op
       const Matrix_Crtp<M_TYPE>& M,         // M
       const Vector_Crtp<V_1_TYPE>& v_1,     // v_1
       const _plus_t_,                       // +
       const Element_Type_t<M_TYPE>& beta,   // β
       const _vector_0_t_                    // v_0

  )
  {
    expr(Expr_Selector<>(),            //
         v_0.impl(),                   // v_0
         _assign_t_(),                 // =
         alpha,                        // α
         _matrix_unary_op_t_<OP_M>(),  // op
         M.impl(),                     // M
         v_1.impl(),                   // v_1
         _plus_t_(),                   // +
         beta,                         // β
         _vector_0_t_()                // v_0
    );
  }
}
