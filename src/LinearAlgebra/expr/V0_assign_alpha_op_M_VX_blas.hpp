//
// Blas routines for
//
//   V0 = α op(M) V1
//
#pragma once

#include "LinearAlgebra/expr/V0_assign_alpha_V0.hpp"

#include "LinearAlgebra/expr/V0_assign_alpha_op_M_V0_driver.hpp"
// TODO #include "LinearAlgebra/expr/V0_assign_alpha_op_M_V1_driver.hpp"

#include "LinearAlgebra/utils/all_same_type.hpp"

#include "LinearAlgebra/blas/blas.hpp"



#if (HAS_BLAS)

namespace LinearAlgebra
{
  //================================================================
  // trmv
  //================================================================
  //
  template <typename V0_TYPE, Matrix_Unary_Op_Enum M_OP, typename M_TYPE>
  auto
  assign(const Expr_Selector<Expr_Selector_Enum::Blas> selected,  // Undefined implementation
         Dense_Vector_Crtp<V0_TYPE>& v0,                          // v0 =
         const Common_Element_Type_t<V0_TYPE, M_TYPE> alpha,      // alpha
         const _matrix_unary_op_t_<M_OP> op,                      // op
         const Dense_Matrix_Crtp<M_TYPE>& M,                      // M
         const _lhs_t_                                            // lhs
         )
      -> std::enable_if_t<
          // Supported matrix op?
          Blas::Support_CBlas_Transpose_v<M_OP> &&
              // Same scalar everywhere
              All_Same_Type_v<Element_Type_t<M_TYPE>, Element_Type_t<V0_TYPE>> &&
              // Scalar support
              Is_CBlas_Supported_Scalar_v<Element_Type_t<M_TYPE>> &&
              // Triangular Matrix
              Blas::Support_CBlas_Diag_v<M_TYPE::matrix_special_structure_type::value>,
          Expr_Selector_Enum>
  {
    assert(M.I_size() == M.J_size());  // TODO: extend to the rectangular case

    assign(v0,alpha,_lhs_);
    
    Blas::trmv(CblasColMajor, Blas::To_CBlas_UpLo_v<M_TYPE::matrix_storage_mask_type::value>,
               Blas::To_CBlas_Transpose_v<M_OP>,
               Blas::To_CBlas_Diag_v<M_TYPE::matrix_special_structure_type::value>, M.I_size(),
               M.data(), M.leading_dimension(), v0.data(), v0.increment());

    return selected;
  }

}

#endif