test_array = [
  ['expr_tags_test','expr_tags_exe','expr_tags.cpp'],

  ['dimension_test','dimension_exe','dimension.cpp'],

  ['V0_assign_alpha_test','V0_assign_alpha_exe','V0_assign_alpha.cpp'],
  ['M0_assign_alpha_test','M0_assign_alpha_exe','M0_assign_alpha.cpp'],
  
  ['V0_assign_V1_test','V0_assign_V1_exe','V0_assign_V1.cpp'], 
  ['M0_assign_M1_test','M0_assign_M1_exe','M0_assign_M1.cpp'], 

  ['X0_assign_alpha_X0_test','X0_assign_alpha_X0_exe','X0_assign_alpha_X0.cpp'],
  
  ['V_assign_V_plus_alpha_V_test','V_assign_V_plus_alpha_V_exe','V_assign_V_plus_alpha_V.cpp'], # en cours

  ['V0_assign_alpha_V0_plus_beta_op_M_V1_test','V0_assign_alpha_V0_plus_beta_op_M_V1_exe','V0_assign_alpha_V0_plus_beta_op_M_V1.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


