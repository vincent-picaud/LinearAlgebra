test_array = [
  'metaexpr_crtp',

  'call_assign_from_metaexpr',

  'some_expressions',

  'V0_assign_alpha_op_M_VX_header',
  
  'V0_assign_alpha_op_M_V1_plus_beta_VX_header',

  'V0_assign_alpha_V1_plus_V0',

  'operator_overloading',
]

foreach test : test_array
  test(test+'_test',
       executable(test+'_exe',
		  test+'.cpp',
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


