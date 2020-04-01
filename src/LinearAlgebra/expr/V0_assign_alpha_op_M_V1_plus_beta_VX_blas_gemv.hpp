//
// blas gemv routine for
//
//   V0 = α op(M) V1 + β V2
//
#pragma once

#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_plus_beta_V2_driver.hpp"
#include "LinearAlgebra/utils/all_same_type.hpp"

#include "LinearAlgebra/blas/blas.hpp"

#if (HAS_BLAS)

namespace LinearAlgebra
{
  //================================================================
  // V0 = α op(M) V1 + β V0
  //================================================================
  //

  template <typename V_0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE, typename V_1_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,
         Dense_Vector_Crtp<V_0_TYPE>& v_0,                               // v_0 =
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> alpha,  // alpha
         const _matrix_unary_op_t_<M_OP> op,                             // op
         const Dense_Matrix_Crtp<M_TYPE>& M,                             // M
         const Dense_Vector_Crtp<V_1_TYPE>& v_1,                         // v_1
         const _plus_t_,                                                 // +
         const Common_Element_Type_t<V_0_TYPE, V_1_TYPE, M_TYPE> beta,   // beta
         const _lhs_t_)                                                  // v_0
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<M_OP> &&
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<M_TYPE>, Element_Type_t<V_0_TYPE>,
                              Element_Type_t<V_1_TYPE>> &&
              // Scalar support
              Is_CBlas_Supported_Scalar_v<Element_Type_t<M_TYPE>> &&
              // Generic matrix
              (M_TYPE::matrix_special_structure_type::value == Matrix_Special_Structure_Enum::None),
          Expr_Selector_Enum>
  {
    Blas::gemv(CblasColMajor, Blas::To_CBlas_Transpose_v<M_OP>, M.I_size(), M.J_size(), alpha,
               M.data(), M.leading_dimension(), v_1.data(), v_1.increment(), beta, v_0.data(),
               v_0.increment());
    return selected;
  }

}

#endif