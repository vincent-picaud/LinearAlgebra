test_array = [
  ['is_std_integral_constant_test','is_std_integral_constant_exe','is_std_integral_constant.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


