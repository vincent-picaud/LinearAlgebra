LinearAlgebra_headers += [
  'expr/expr_tags.hpp',
  'expr/expr_selector.hpp',
  'expr/dimension.hpp',


  # OK
  'expr/X_eq_alpha_vector.hpp', 
  'expr/X_eq_alpha_matrix.hpp', 
  'expr/X_eq_alpha/generic_interface.hpp', 
  'expr/X_eq_alpha/vector_impl.hpp', 
  'expr/X_eq_alpha/matrix_impl.hpp', 

  # OK
  'expr/copy_vector.hpp', 
  'expr/copy_matrix.hpp', 
  'expr/copy/generic_interface.hpp', 
  'expr/copy/vector_impl.hpp', 
  'expr/copy/matrix_impl.hpp', 

  # to update! (use copy as model)
  # 'expr/X0_assign_alpha_X0.hpp', 
  # 'expr/V0_assign_alpha_V0.hpp', 
  # 'expr/M0_assign_alpha_M0.hpp',
  'expr/X_eq_aX_vector.hpp', 
  'expr/X_eq_aX_matrix.hpp', 
  'expr/X_eq_aX/generic_interface.hpp', 
  'expr/X_eq_aX/vector_impl.hpp', 
  'expr/X_eq_aX/matrix_impl.hpp', 

  # to update! (use copy as model)
  'expr/X0_assign_alpha_X1_plus_X0.hpp', 
  'expr/V0_assign_alpha_V1_plus_V0.hpp', 
  'expr/M0_assign_alpha_M1_plus_M0.hpp',

  # to update! (use copy as model)
  'expr/X0_assign_alpha_X1_plus_X2.hpp',
  'expr/V0_assign_alpha_V1_plus_V2.hpp',
  'expr/M0_assign_alpha_M1_plus_M2.hpp',

  'expr/vector_expr.hpp', # main header: include all expr 
  'expr/matrix_expr.hpp', # main header: include all expr

  'expr/expr_debug.hpp',

  'expr/M_eq_aMM_bM.hpp', # New approach
  'expr/v_eq_aMv_bv.hpp', # New approach
  'expr/v_eq_aMv.hpp', # New approach

  # scalar_ref introduction
  'expr/scalar_crtp.hpp',     # required to make assign_fallback possible
  'expr/assign_fallback.hpp', # fallback to shorten error messages
  'expr/expr.hpp',            # convenience header file
]

LinearAlgebra_sources += [
  'expr/expr_debug.cpp',
]

subdir('M_eq_aMM_bM')
subdir('v_eq_aMv_bv')
subdir('v_eq_aMv')
