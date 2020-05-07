test_array = [
  'crtp',
  'is_std_integral_constant',
  'size_utils',
  'is_complete',
  'all_same_type',
  'element_type',
  'has_static_dimension',
  'same_mathematical_object_p',
  'enum_class_to_value',
  'lower_upper_bound',
]

foreach test : test_array
  test(test+'_test',
       executable(test+'_exe',
		  test+'.cpp',
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


