LinearAlgebra_headers += [
  'expr/expr_tags.hpp',
  'expr/expr_selector.hpp',
  'expr/dimension.hpp',

  'expr/vector_expr.hpp', # main header: include all expr 
  'expr/matrix_expr.hpp', # main header: include all expr

  'expr/expr_debug.hpp',


  # scalar_ref introduction
  'expr/scalar_crtp.hpp',     # required to make assign_fallback possible
  'expr/assign_fallback.hpp', # fallback to shorten error messages
  'expr/expr.hpp',            # convenience header file

  # ################################################################
  # New approach
  # ################################################################

  # ================================================================
  # Copy
  # ================================================================
  #
  'expr/copy.hpp', 
  'expr/copy/generic.hpp', 
  'expr/copy/vector.hpp', 
  'expr/copy/matrix.hpp', 

  # ================================================================
  # X_eq_neg_X
  # ================================================================
  #
  'expr/X_eq_neg_X.hpp', 
  'expr/X_eq_neg_X/vector.hpp', 
  'expr/X_eq_neg_X/matrix.hpp', 
  'expr/X_eq_neg_X/generic.hpp', 

  # ================================================================
  # X_eq_neg_X
  # ================================================================
  #
  'expr/X_eq_aX.hpp', 
  'expr/X_eq_aX/generic.hpp', 
  'expr/X_eq_aX/vector.hpp', 
  'expr/X_eq_aX/matrix.hpp', 

  # ================================================================
  # M_eq_aMM_bM
  # ================================================================
  #
  'expr/M_eq_aMM_bM.hpp', 
  'expr/M_eq_aMM_bM/blas.hpp', 

  # ================================================================
  # v_eq_aMv_bv
  # ================================================================
  #
  'expr/v_eq_aMv_bv.hpp', 
  'expr/v_eq_aMv_bv/blas.hpp', 

  # ================================================================
  # v_eq_aMv
  # ================================================================
  #
  'expr/v_eq_aMv.hpp',
  'expr/v_eq_aMv/blas.hpp',

  # ================================================================
  # v_eq_a_inv_Mv
  # ================================================================
  #
  'expr/v_eq_a_inv_Mv.hpp',
  'expr/v_eq_a_inv_Mv/blas.hpp',


  # ################################################################
  # Old one
  # ################################################################
  
  # OK
  'expr/X_eq_alpha_vector.hpp', 
  'expr/X_eq_alpha_matrix.hpp', 
  'expr/X_eq_alpha/generic_interface.hpp', 
  'expr/X_eq_alpha/vector_impl.hpp', 
  'expr/X_eq_alpha/matrix_impl.hpp', 
 
  # to update! (use copy as model)
  'expr/X0_assign_alpha_X1_plus_X0.hpp', 
  'expr/V0_assign_alpha_V1_plus_V0.hpp', 
  'expr/M0_assign_alpha_M1_plus_M0.hpp',

  # to update! (use copy as model)
  'expr/X0_assign_alpha_X1_plus_X2.hpp',
  'expr/V0_assign_alpha_V1_plus_V2.hpp',
  'expr/M0_assign_alpha_M1_plus_M2.hpp',
]

LinearAlgebra_sources += [
  'expr/expr_debug.cpp',
]

