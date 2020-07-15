test_array = [
  'expr_tags',

  'dimension',

  'V0_assign_alpha',
  'M0_assign_alpha',
  
  'V0_assign_V1',
  'M0_assign_M1',

  'X_eq_aX',
  
  'X0_assign_alpha_X1_plus_X0',

  'V0_assign_alpha_op_M_V1_plus_beta_V0',

  'V0_assign_alpha_op_M_VX_header',

  # new implementation 
  'M_eq_aMM_bM',
  'v_eq_aMv_bv',

  # TODO 'v_eq_aMv',
  'v_eq_a_inv_Mv',

  'X_eq_neg_X'
]

foreach test : test_array
  test(test+'_test',
       executable(test+'_exe',
		  test+'.cpp',
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


