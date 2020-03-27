test_array = [
  ['expr_tags_test','expr_tags_exe','expr_tags.cpp'],

  ['dimension_test','dimension_exe','dimension.cpp'],

  ['V0_assign_V1_test','V0_assign_V1_exe','V0_assign_V1.cpp'],
  ['M0_assign_M1_test','M0_assign_M1_exe','M0_assign_M1.cpp'],
  
  ['V0_assign_V0_plus_alpha_V1_test','V0_assign_V0_plus_alpha_V1_exe','V0_assign_V0_plus_alpha_V1.cpp'],

  ['V0_assign_alpha_V0_plus_beta_op_M_V1_test','V0_assign_alpha_V0_plus_beta_op_M_V1_exe','V0_assign_alpha_V0_plus_beta_op_M_V1.cpp'],

  ['M0_assign_alpha_M0_plus_beta_V0_op_V0_test','M0_assign_alpha_M0_plus_beta_V0_op_V0_exe','M0_assign_alpha_M0_plus_beta_V0_op_V0.cpp'],

  #
  ['V_assign_alpha_test','V_assign_alpha_exe','V_assign_alpha.cpp'],
  ['M_assign_alpha_test','M_assign_alpha_exe','M_assign_alpha.cpp'],
  
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


