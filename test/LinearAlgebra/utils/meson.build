test_array = [
  ['crtp_test','crtp_exe','crtp.cpp'],
  ['is_std_integral_constant_test','is_std_integral_constant_exe','is_std_integral_constant.cpp'],
  ['size_utils_test','size_utils_exe','size_utils.cpp'],
  ['is_complete_test','is_complete_exe','is_complete.cpp'],
  ['all_same_type_test','all_same_type_exe','all_same_type.cpp'],
  ['element_type_test','element_type_exe','element_type.cpp'],
  ['has_static_dimension_test','has_static_dimension_exe','has_static_dimension.cpp'],
  ['same_mathematical_object_p_test','same_mathematical_object_p_exe','same_mathematical_object_p.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


