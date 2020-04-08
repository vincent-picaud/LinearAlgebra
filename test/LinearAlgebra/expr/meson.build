test_array = [
  ['expr_tags_test','expr_tags_exe','expr_tags.cpp'],

  ['dimension_test','dimension_exe','dimension.cpp'],

  ['V0_assign_alpha_test','V0_assign_alpha_exe','V0_assign_alpha.cpp'],
  ['M0_assign_alpha_test','M0_assign_alpha_exe','M0_assign_alpha.cpp'],
  
  ['V0_assign_V1_test','V0_assign_V1_exe','V0_assign_V1.cpp'], 
  ['M0_assign_M1_test','M0_assign_M1_exe','M0_assign_M1.cpp'], 

  ['X0_assign_alpha_X0_test','X0_assign_alpha_X0_exe','X0_assign_alpha_X0.cpp'],
  ['X0_assign_alpha_X1_test','X0_assign_alpha_X1_exe','X0_assign_alpha_X1.cpp'],
  
  ['X0_assign_alpha_X1_plus_X0_test','X0_assign_alpha_X1_plus_X0_exe','X0_assign_alpha_X1_plus_X0.cpp'], 

  ['V0_assign_alpha_op_M_V1_plus_beta_V0_test','V0_assign_alpha_op_M_V1_plus_beta_V0_exe','V0_assign_alpha_op_M_V1_plus_beta_V0.cpp'],

#  ['V0_assign_alpha_op_M_VX_header_test','V0_assign_alpha_op_M_VX_header_exe','V0_assign_alpha_op_M_VX_header.cpp'],
  
  # ['M_eq_aMM_bM_test','M_eq_aMM_bM_exe','M_eq_aMM_bM.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


