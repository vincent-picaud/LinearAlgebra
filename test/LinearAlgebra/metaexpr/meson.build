test_array = [
  ['metaexpr_crtp_test','metaexpr_crtp_metaexe','metaexpr_crtp.cpp'],
  ['call_assign_from_metaexpr_test','call_assign_from_metaexpr_metaexe','call_assign_from_metaexpr.cpp'],
  ['some_expressions_test','some_expressions_metaexe','some_expressions.cpp'],

  ['V0_assign_alpha_op_M_VX_header_test','V0_assign_alpha_op_M_VX_header_metaexe','V0_assign_alpha_op_M_VX_header.cpp'],
  
  ['V0_assign_alpha_op_M_V1_plus_beta_VX_header_test','V0_assign_alpha_op_M_V1_plus_beta_VX_header_metaexe','V0_assign_alpha_op_M_V1_plus_beta_VX_header.cpp'],

  ['V0_assign_alpha_V1_plus_V0_test','V0_assign_alpha_V1_plus_V0_metaexe','V0_assign_alpha_V1_plus_V0.cpp'],

  
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


