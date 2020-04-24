test_array = [
  'dot_vector',
  'norm_2_vector',
  'dist_2_vector',
  'norm_inf_vector',
]

foreach test : test_array
  test(test+'_test',
       executable(test+'_exe',
		  test+'.cpp',
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


